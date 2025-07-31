#ifndef EXAMPLES_H
#define EXAMPLES_H

#include <stdint.h>

// -------------------------------------------------------------------------------------------------------------------
// Example displays
// -------------------------------------------------------------------------------------------------------------------

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

// -- Drawing an example triangle pattern on the display
void draw_diagonal_traingle(void);

#endif // EXAMPLES_H
