#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// -------------------------------------------------------------------------------------------------------------------
// Utility functions
// -------------------------------------------------------------------------------------------------------------------

// -- Screen brightness management
void screen_fade(uint8_t max_brightness);
void draw_brightness_frame(uint8_t brightness_level);

#endif // UTILS_H
