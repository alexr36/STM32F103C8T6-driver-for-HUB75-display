#include "utils.h"
#include "oe_control.h"
#include "hub75.h"

// ----------------------------------------------------------------------------
// Utility functions
// ----------------------------------------------------------------------------

/**
  * @brief  Brightens and dims the screen using PWM.
  * @param  max_brightness: determines maximum brightness level (0-100)
  * @retval None
  */
void PWM_screen_fade(uint8_t max_brightness)
{
  if (max_brightness > 100) max_brightness = 100;

  for (int b = 1; b <= max_brightness; b++)
  {
	  draw_brightness_frame(b);
	  HAL_Delay(50);
  }
  HAL_Delay(1000);

  for (int b = max_brightness; b >= 1; b--)
  {
	  draw_brightness_frame(b);
	  HAL_Delay(50);
  }
  HAL_Delay(1000);
}

/**
  * @brief  Changes frame's brightness and displays the frame.
  * @retval None
  */
void draw_brightness_frame(uint8_t brightness_level)
{
  OE_set_brightness(brightness_level);
  //draw_framebuffer();
}
