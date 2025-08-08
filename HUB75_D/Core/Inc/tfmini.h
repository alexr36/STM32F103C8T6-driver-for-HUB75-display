/**
  ******************************************************************************
  * @file           : tfmini.h
  * @brief          : Header for tfmini.c file.
  *                   This file conatins all definitions required
  *                   for proper collecting of velocity data.
  ******************************************************************************
  */

#ifndef TFMINI_H
#define TFMINI_H

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------
#include <stdint.h>

// -----------------------------------------------------------------------------
// Required constants
// -----------------------------------------------------------------------------
#define TFmini_FRAME_SIZE  9

// -----------------------------------------------------------------------------
// Variables
// -----------------------------------------------------------------------------
extern volatile uint16_t TFmini_distance;
extern volatile uint8_t  TFmini_frame_ready;

// -----------------------------------------------------------------------------
// Functions for collecting data and calculating velocity
// -----------------------------------------------------------------------------

// -- Collecting data from USART device ----------------------------------------
void  TFmini_UART_Init_DMA(void);

// -- Validating dataframe -----------------------------------------------------
int   is_header_valid(void);
int   is_checksum_valid(void);

// -- Calculating speed --------------------------------------------------------
float calculate_speed(uint16_t dist_1, uint16_t dist_2, uint32_t time_delta);
void  process_velocity(void);

#endif //TFMINI_H
