#ifndef HUB75_H
#define HUB75_H

#include <stdint.h>

// -------------------------------------------------------------------------------------------------------------------
// Display geometry
// -------------------------------------------------------------------------------------------------------------------
#define PANEL_WIDTH 	  64
#define PANEL_HEIGHT 	  64
#define PANEL_HEIGHT_HALF PANEL_HEIGHT / 2
#define RGB2_PINS_OFFSET  16

// -------------------------------------------------------------------------------------------------------------------
// Pins and ports
// -------------------------------------------------------------------------------------------------------------------

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
#define LAT_PIN GPIO_PIN_7	// B7

// -------------------------------------------------------------------------------------------------------------------
// RGB frame buffer
// -------------------------------------------------------------------------------------------------------------------
extern uint8_t framebuffer[PANEL_WIDTH][PANEL_HEIGHT][3];

// -------------------------------------------------------------------------------------------------------------------
// Display management functions
// -------------------------------------------------------------------------------------------------------------------

// -- GPIO manipulation
void delay_short(int reps);
void clock_pulse(void);
void latch_data(void);
void output_enable(uint8_t enable);
void set_row(uint8_t row);

// -- Configuration
void clear_framebuffer(void);
void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
int is_coordinate_on_screen(const uint8_t x, const uint8_t y);

// -- Drawing
void draw_framebuffer(void);
void draw_row(uint8_t row, uint8_t offset);
void draw_rgb565_bitmap(const uint16_t* bmp_ptr);

#endif // HUB75_H
