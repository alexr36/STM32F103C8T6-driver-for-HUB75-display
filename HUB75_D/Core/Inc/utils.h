#ifndef UTILS_H
#define UTILS_H

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------
#include <stdint.h>

// ----------------------------------------------------------------------------
// Utility functions
// ----------------------------------------------------------------------------

// -- Screen brightness management
void PWM_screen_fade(uint8_t max_brightness);
void draw_brightness_frame(uint8_t brightness_level);

#endif // UTILS_H
