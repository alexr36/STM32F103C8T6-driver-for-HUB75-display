#include "hub75.h"
#include "stm32f1xx_hal.h"
#include "cmsis_gcc.h"
#include "utils.h"

// ----------------------------------------------------------------------------
// RGB frame buffer and row counter
// ----------------------------------------------------------------------------
uint8_t framebuffer[PANEL_WIDTH][PANEL_HEIGHT][3];
static uint8_t current_row = 0;

// ----------------------------------------------------------------------------
// Display management functions
// ----------------------------------------------------------------------------

// -- GPIO manipulation

/**
  * @brief  Short software delay using NOPs.
  * @param  reps: Number of repetitions.
  * @retval None
  */
void delay_short(int reps)
{
  for (volatile int i = 0; i < reps; ++i) __NOP();
}

/**
  * @brief  Generates a single clock pulse.
  * @retval None
  */
void clock_pulse(void)
{
//  HAL_GPIO_WritePin(PORT_A, CLK_PIN, GPIO_PIN_SET);
//  //delay_short(1);
//  HAL_GPIO_WritePin(PORT_A, CLK_PIN, GPIO_PIN_RESET);

  // Equivalent of the code above but faster
  PORT_A->BSRR = CLK_PIN;
  PORT_A->BRR  = CLK_PIN;
}

/**
  * @brief  Sends latch pulse to shift registers.
  * @retval None
  */
void latch_data(void)
{
//  HAL_GPIO_WritePin(PORT_B, LAT_PIN, GPIO_PIN_SET);
//  //delay_short(1);
//  HAL_GPIO_WritePin(PORT_B, LAT_PIN, GPIO_PIN_RESET);

  // Equivalent of the code above but faster
  PORT_B->BSRR = LAT_PIN;
  PORT_B->BRR  = LAT_PIN;
}

/**
  * @brief  Controls Output Enable (OE) pin.
  * @param  enable: 1 = enabled (LOW), 0 = disabled (HIGH).
  * @retval None
  */
void output_enable(uint8_t enable)
{
//  HAL_GPIO_WritePin(PORT_B, OE_PIN, enable ? GPIO_PIN_RESET : GPIO_PIN_SET);

  // Equivalent of the code above but faster
  if (enable) PORT_B->BRR   = OE_PIN;
  else		  PORT_B->BSRR  = OE_PIN;
}

/**
  * @brief  Sets active HUB75 row based on A, B, C and D pins.
  * @param  row: Row index (0-15).
  * @retval None
  */
void set_row(uint8_t row)
{
  if (row >= RGB2_PINS_OFFSET) return;

//  HAL_GPIO_WritePin(PORT_B, A_PIN, (row & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(PORT_B, B_PIN, (row & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(PORT_B, C_PIN, (row & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(PORT_B, D_PIN, (row & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  // Reset all pins
  PORT_B->BRR = A_PIN | B_PIN | C_PIN | D_PIN;

  // Set pins based on row number
  if (row & 0x01) PORT_B->BSRR = A_PIN;
  if (row & 0x02) PORT_B->BSRR = B_PIN;
  if (row & 0x04) PORT_B->BSRR = C_PIN;
  if (row & 0x08) PORT_B->BSRR = D_PIN;
}


// -- Configuration

/**
  * @brief  Clears the entire framebuffer by setting all pixels to black.
  * @retval None
  */
void clear_framebuffer(void)
{
  for (int x = 0; x < PANEL_WIDTH; x++)
  {
    for (int y = 0; y < PANEL_HEIGHT; y++)
    {
      framebuffer[x][y][0] = 0;
      framebuffer[x][y][1] = 0;
      framebuffer[x][y][2] = 0;
    }
  }
}

/**
  * @brief  Sets a pixel in framebuffer to display an RGB color.
  * @param  x: X coordinate (0-64)
  * @param  y: Y coordinate (0-64)
  * @param  r: Red channel (0 or 1)
  * @param  g: Green channel (0 or 1)
  * @param  b: Blue channel (0 or 1)
  * @retval None
  */
void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b)
{
  if (x >= PANEL_WIDTH || y >= PANEL_HEIGHT) return;

  framebuffer[x][y][0] = r;
  framebuffer[x][y][1] = g;
  framebuffer[x][y][2] = b;
}

/**
  * @brief  Checks if given coordinates are within the display range.
  * @param  x: X coordinate
  * @param  y: Y coordinate
  * @retval int
  */
int is_coordinate_on_screen(const uint8_t x, const uint8_t y)
{
  return (x >= 0 && x < PANEL_WIDTH && y >= 0 && y < PANEL_HEIGHT);
}

/**
  * @brief  Draws the entire framebuffer on the screen.
  * @retval None
  */
void draw_framebuffer(void)
{
  for (uint8_t row = 0; row < RGB2_PINS_OFFSET; row++) {
	output_enable(0);

    set_row(row);   // <- Logically it should be put here but doesn't work in a loop
	draw_row(row, 0);
	draw_row(row, PANEL_HEIGHT_HALF);
	latch_data();

	output_enable(1);
	delay_short(2750);
  }
}

/**
  * @brief  Draws a row from framebuffer (2 panel halves).
  * @param  row: row index (0-15)
  * @param  offset: offset value (0 or 32)
  * @retval None
  */
void draw_row(uint8_t row, uint8_t offset)
{
  if (offset != 0 && offset != PANEL_HEIGHT_HALF) return;

  uint8_t upper;
  uint8_t lower;

  for (int col = 0; col < PANEL_WIDTH; col++)
  {
	upper = row + offset;
	lower = upper + RGB2_PINS_OFFSET;

//    HAL_GPIO_WritePin(PORT_A, R1_PIN, framebuffer[col][upper][0] ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(PORT_A, G1_PIN, framebuffer[col][upper][1] ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(PORT_A, B1_PIN, framebuffer[col][upper][2] ? GPIO_PIN_SET : GPIO_PIN_RESET);
//
//    HAL_GPIO_WritePin(PORT_A, R2_PIN, framebuffer[col][lower][0] ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(PORT_A, G2_PIN, framebuffer[col][lower][1] ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(PORT_A, B2_PIN, framebuffer[col][lower][2] ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // Reset all pins
    PORT_A->BRR = R1_PIN | G1_PIN | B1_PIN | R2_PIN | G2_PIN | B2_PIN;

    // Set pins based on row and col number
    if (framebuffer[col][upper][0]) PORT_A->BSRR = R1_PIN;
    if (framebuffer[col][upper][1]) PORT_A->BSRR = G1_PIN;
    if (framebuffer[col][upper][2]) PORT_A->BSRR = B1_PIN;

    if (framebuffer[col][lower][0]) PORT_A->BSRR = R2_PIN;
    if (framebuffer[col][lower][1]) PORT_A->BSRR = G2_PIN;
    if (framebuffer[col][lower][2]) PORT_A->BSRR = B2_PIN;

    clock_pulse();
  }
}

/**
  * @brief  Draws given bitmap on the screen.
  * @param  bmp_ptr: pointer to the bitmap
  * @retval None
  */
void draw_rgb565_bitmap(const uint16_t* bmp_ptr)
{
  for (uint8_t y = 0; y < PANEL_HEIGHT; y++)
  {
    for (uint8_t x = 0; x < PANEL_WIDTH; x++)
    {
      uint16_t pixel = bmp_ptr[y * PANEL_WIDTH + x];

      // Extracting colors from RGB565
      uint8_t r_5 = (pixel >> 11) & 0x1F;
      uint8_t g_6 = (pixel >>  5) & 0x3F;
      uint8_t b_5 =  pixel        & 0x1F;

      // Convert to 255-bit color value
      uint8_t r = (r_5 << 3) | (r_5 >> 2);
      uint8_t g = (g_6 << 2) | (g_6 >> 4);
      uint8_t b = (b_5 << 3) | (b_5 >> 2);

      set_pixel(x, y, r, g, b);
    }
  }

  draw_framebuffer();
}

/**
  * @brief  Updates rows displayed on the screen
  *         (Intended to use with Timer Interruption).
  * @retval None
  */
void draw_row_update(void)
{
  set_row(current_row);
  draw_row(current_row, 0);
  draw_row(current_row, PANEL_HEIGHT_HALF);
  latch_data();

  current_row++;
  if (current_row >= RGB2_PINS_OFFSET) current_row = 0;
}
