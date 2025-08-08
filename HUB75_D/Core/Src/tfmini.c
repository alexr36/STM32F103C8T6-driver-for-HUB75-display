/**
  ******************************************************************************
  * @file           : tfmini.c
  * @brief          : TFmini Plus integration with STM32F103C8T6 via USART
  *                   and velocity data processing.
  ******************************************************************************
  */

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------
#include <stdlib.h>

#include "stm32f1xx_hal.h"
#include "tfmini.h"
#include "hub75.h"
#include "utils.h"
#include "examples.h"

// -----------------------------------------------------------------------------
// Variables
// -----------------------------------------------------------------------------
extern UART_HandleTypeDef huart1;

uint8_t  UART_rx_byte;
uint8_t  TFmini_frame_buffer[TFmini_FRAME_SIZE];
uint8_t  TFmini_frame_index = 0;
uint32_t tick_last          = 0;
uint16_t distance_prev      = 0;
uint8_t  speed_last         = 0;
int      is_drawn           = 2;

volatile uint16_t TFmini_distance    = 0;
volatile uint8_t  TFmini_frame_ready = 0;

// -----------------------------------------------------------------------------
// Functions for collecting data and calculating velocity
// -----------------------------------------------------------------------------

// -- Collecting data from USART device ----------------------------------------

/**
  * @brief  Initializes UART to receive data during interrupt.
  * @retval None
  */
void TFmini_UART_Init_DMA(void)
{
  HAL_UART_Receive_DMA(&huart1, TFmini_frame_buffer, TFmini_FRAME_SIZE);
}

/**
  * @brief  Callback function, called during UART interrupt
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance != USART1) return;

  if (is_header_valid() && is_checksum_valid())
  {
	// Little endian format
	TFmini_distance = TFmini_frame_buffer[2] | (TFmini_frame_buffer[3] << 8);
    TFmini_frame_ready = 1;
  }

  TFmini_UART_Init_DMA();
}


// -- Validating dataframe -----------------------------------------------------

/**
  * @brief  Checks if dataframe header is valid
  * @retval int
  */
int is_header_valid(void)
{
  return TFmini_frame_buffer[0] == 0x59 && TFmini_frame_buffer[1] == 0x59;
}

/**
  * @brief  Checks if dataframe checksum is valid
  * @retval int
  */
int is_checksum_valid()
{
  uint16_t checksum = 0;
  for (uint8_t i = 0; i < 8; i++) checksum += TFmini_frame_buffer[i];

  return ((checksum & 0xFF) == TFmini_frame_buffer[8]);
}


// -- Calculating speed --------------------------------------------------------

/**
  * @brief  Calculates speed based on given arguments.
  * @param  dist_1: First measured distance (cm)
  * @param  dist_2: Second measured distance (cm)
  * @param  time_delta: Difference between measured times (ms)
  * @retval float
  */
float calculate_speed(uint16_t dist_1, uint16_t dist_2, uint32_t time_delta)
{
  if (time_delta == 0) return 0;

  // |v| = (|dist_1 - dist_2| / 100) / (time_delta / 1000) * 3.6
  return (abs((int)dist_1 - (int)dist_2) / 100.0f) / (time_delta / 1000.0f) * 3.6f;
}

/**
  * @brief  Gathers data required to calculate speed and displays it.
  * @retval None
  */
void process_speed(void)
{
  if (!TFmini_frame_ready) return;

  TFmini_frame_ready = 0;

  uint32_t tick_now     = HAL_GetTick();
  uint16_t distance_now = TFmini_distance;

  if (distance_now == 0 || distance_now == 0xFFFF) return;

  if (tick_last != 0)
  {
	uint8_t speed_current = calculate_speed(distance_now, distance_prev, tick_now - tick_last);

	if (speed_current != speed_last)
	{
	  speed_last = speed_current;
	  clear_framebuffer();
	}

	draw_speed(speed_current);
  }

  distance_prev = distance_now;
  tick_last     = tick_now;
  HAL_Delay(500);
}


// -- Displaying traffic signs based on detected distance ----------------------

/**
  * @brief  Turns off and on TIM3 Interrupts in order to avoid screen
  *         flickering while dynamically changing the displayed bitmap.
  * @param  id_drawn_updated_state: Updated 'is_drawn' flag value of currently displayed traffic sign
  * @param  draw_bitmap: Pointer to a function responsible for drawing a certain traffic sign
  * @retval None
  */
void omit_flickering(uint8_t is_drawn_updated_state, void (*draw_bitmap)(void))
{
  HAL_NVIC_DisableIRQ(TIM3_IRQn);
  clear_framebuffer();
  is_drawn = is_drawn_updated_state;
  (*draw_bitmap)();
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

/**
  * @brief  Displays STOP or AHEAD ONLY traffic sign
  *         based on safe distance to the object.
  * @retval None
  */
void inform_about_object(void)
{
  if (!TFmini_frame_ready) return;

  TFmini_frame_ready = 0;

  uint32_t tick_now     = HAL_GetTick();
  uint16_t distance_now = TFmini_distance;

  if (distance_now == 0 || distance_now == 0xFFFF) return;

  if (tick_last != 0)
  {
    if      (distance_now < SAFE_DISTANCE_CM  && is_drawn != 0) omit_flickering(0, draw_STOP_bitmap);
    else if (distance_now >= SAFE_DISTANCE_CM && is_drawn != 1) omit_flickering(1, draw_AHEAD_ONLY_bitmap);
  }

  tick_last = tick_now;
  HAL_Delay(500);
}

