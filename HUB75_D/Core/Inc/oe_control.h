#ifndef __OE_CONTROL_H
#define __OE_CONTROL_H

// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------
#include <stdint.h>

// ----------------------------------------------------------------------------
// Output Enable (OE) pin manipulation functions
// ----------------------------------------------------------------------------

void OE_PWM_Init(void);
void OE_set_brightness(uint8_t brightness_percent);

#endif // __OE_CONTROL_H
