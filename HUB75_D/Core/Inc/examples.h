/**
  ******************************************************************************
  * @file           : examples.h
  * @brief          : Header for examples.c file.
  *                   This file conatins all definitons required
  *                   for the example functions to be executed flawlessly.
  ******************************************************************************
  */

#ifndef EXAMPLES_H
#define EXAMPLES_H

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------
#include <stdint.h>

// ----------------------------------------------------------------------------
// Example display functions
// ----------------------------------------------------------------------------

// -- Drawing a cross of four different colors on diagonals of the display
void draw_test_cross(void);

// -- Drawing snake pattern on the display
void draw_snake_pattern_in(uint8_t r, uint8_t g, uint8_t b);
void draw_snake_pattern_out(uint8_t r, uint8_t g, uint8_t b);
void draw_snake_go_in_out(void);

// -- Drawing an example bitmap
void draw_W_bitmap(void);
void draw_STOP_bitmap(void);
void draw_AHEAD_ONLY_bitmap(void);
void draw_RIBBON_bitmap(void);

// -- Drawing an example triangle pattern on the display
void draw_diagonal_traingle(void);

// -- Drawing a random speed value on the display
void draw_random_speed(void);

#endif // EXAMPLES_H
