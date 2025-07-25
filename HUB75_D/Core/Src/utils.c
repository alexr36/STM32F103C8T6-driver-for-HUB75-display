#include "utils.h"


/**
  * @brief  Brightens and dims the screen.
  * @param  max_brightness: determines maximum brightness level (0-100)
  * @retval None
  */
void screen_fade(uint8_t max_brightness)
{
  if (max_brightness > 100) max_brightness = 100;

  for (int b = 2; b <= max_brightness; b++) draw_brightness_frame(b);
  for (int b = max_brightness; b >= 2; b--) draw_brightness_frame(b);
}

/**
  * @brief  Changes frame's brightness and displays the frame.
  * @retval None
  */
void draw_brightness_frame(uint8_t brightness_level)
{
  OE_set_brightness(brightness_level);
  draw_framebuffer();
}
