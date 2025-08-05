/**
  ******************************************************************************
  * @file           : hub75.h
  * @brief          : Header for hub75.c file.
  *                   This file conatins all definitions required
  *                   for proper app's parameters configuration.
  ******************************************************************************
  */

#ifndef HUB75_H
#define HUB75_H

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------
#include <stdint.h>

// -----------------------------------------------------------------------------
// Display geometry
// -----------------------------------------------------------------------------
#define PANEL_WIDTH 	  64
#define PANEL_HEIGHT 	  64
#define PANEL_HEIGHT_HALF PANEL_HEIGHT / 2
#define RGB2_PINS_OFFSET  16

// -----------------------------------------------------------------------------
// Pins and ports
// -----------------------------------------------------------------------------

/* Change definitions by mapping them according to user's own configuration!  */

// -- Pins of port A
#define PORT_A  GPIOA
#define R1_PIN  GPIO_PIN_0  // A0
#define G1_PIN  GPIO_PIN_1  // A1
#define B1_PIN  GPIO_PIN_2  // A2
#define R2_PIN  GPIO_PIN_3  // A3
#define G2_PIN  GPIO_PIN_4  // A4
#define B2_PIN  GPIO_PIN_5  // A5
#define CLK_PIN GPIO_PIN_15 // A15

// -- Pins of port B
#define PORT_B  GPIOB
#define OE_PIN  GPIO_PIN_0  // B0
#define D_PIN   GPIO_PIN_3  // B3
#define C_PIN   GPIO_PIN_4  // B4
#define B_PIN   GPIO_PIN_5  // B5
#define A_PIN   GPIO_PIN_6  // B6
#define LAT_PIN GPIO_PIN_7  // B7

#define OE_ON   output_enable(1)
#define OE_OFF  output_enable(0)

// -----------------------------------------------------------------------------
// Speed display configuration
// -----------------------------------------------------------------------------
#define SAFE_SPEED_LIMIT 30

// -----------------------------------------------------------------------------
// RGB frame buffer
// -----------------------------------------------------------------------------
extern uint8_t  framebuffer[PANEL_WIDTH][PANEL_HEIGHT][3];
extern uint16_t brightness_level;
extern int8_t   brightness_increment;
extern uint8_t  row_step;
extern uint8_t  current_row;

// -----------------------------------------------------------------------------
// Display management functions
// -----------------------------------------------------------------------------

// -- GPIO manipulation
void delay_short(int reps);
void clock_pulse(void);
void latch_data(void);
void output_enable(uint8_t enable);
void set_row(uint8_t row);

// -- Configuration
void clear_framebuffer(void);
void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
int  is_coordinate_on_screen(const uint8_t x, const uint8_t y);

// -- Drawing
void draw_framebuffer(void);
void draw_row(uint8_t row, uint8_t offset);
void draw_row_update(void);

// -- Drawing bitmaps
void draw_rgb565_bitmap(const uint16_t* bmp_ptr);

// -- Drawing digits
void draw_digit(uint8_t digit, uint8_t x_offset, uint8_t y_offset, uint8_t r, uint8_t g, uint8_t b);
void draw_speed(uint8_t speed);

// -- Brightness manipulation
void update_brightness(void);
void check_brightness(void);

#endif // HUB75_H
