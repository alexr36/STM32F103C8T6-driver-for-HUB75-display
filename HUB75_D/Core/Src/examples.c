#include "examples.h"
#include "hub75.h"
#include "W.h"

/**
  * @brief  Draws four-coloured cross on display's diagonals.
  * @retval None
  */
void draw_test_cross(void)
{
  for (int i = 0; i < PANEL_WIDTH / 2; i++) set_pixel(i, i, 1, 0, 0);  								   // Red
  for (int i = PANEL_WIDTH / 2; i < PANEL_WIDTH; i++) set_pixel(i, i, 0, 1, 0);  					   // Green
  for (int i = PANEL_WIDTH - 1; i >= PANEL_WIDTH / 2; i--) set_pixel(i, PANEL_WIDTH - 1 - i, 0, 0, 1); // Blue
  for (int i = PANEL_WIDTH / 2 - 1; i >= 0; i--) set_pixel(i, PANEL_WIDTH - 1 - i, 1, 1, 0);  		   // Yellow
}

/**
  * @brief  Draws snake pattern of given color
  *         going from the border to the center.
  * @param  r: Red channel (0-1)
  * @param  g: Green channel (0-1)
  * @param  b: Blue channel (0-1)
  * @retval None
  */
void draw_snake_pattern_in(uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t left = 0;
  uint8_t right = PANEL_WIDTH - 1;
  uint8_t top = 0;
  uint8_t bottom = PANEL_HEIGHT - 1;

  while (left <= right && top <= bottom)
  {
    for (uint8_t x = left; x <= right; x++)
    {
	  set_pixel(x, top, r, g, b);
	  draw_framebuffer();
	}
	top++;

	for (uint8_t y = top; y <= bottom; y++)
	{
      set_pixel(right, y, r, g, b);
	  draw_framebuffer();
	}
	right--;


    if (top <= bottom)
    {
      for (int x = right; x >= left; x--)
      {
        set_pixel(x, bottom, r, g, b);
    	draw_framebuffer();
      }
      bottom--;
    }

    if (left <= right)
    {
      for (int y = bottom; y >= top; y--)
      {
        set_pixel(left, y, r, g, b);
    	draw_framebuffer();
      }
      left++;
    }
  }
}

/**
  * @brief  Draws snake pattern of given color
  *         going from the center to the border.
  * @param  r: Red channel (0-1)
  * @param  g: Green channel (0-1)
  * @param  b: Blue channel (0-1)
  * @retval None
  */
void draw_snake_pattern_out(uint8_t r, uint8_t g, uint8_t b)
{
  int cx = PANEL_WIDTH / 2;
  int cy = PANEL_HEIGHT / 2;

  int x = cx;
  int y = cy;

  int step = 0;

  while (step < PANEL_WIDTH || step < PANEL_HEIGHT)
  {
    for (int i = 0; i < step; i++)
    {
      if (is_coordinate_on_screen(x, y)) set_pixel(x, y, r, g, b);
      draw_framebuffer();
      x++;
    }

    for (int i = 0; i < step; i++)
    {
      if (is_coordinate_on_screen(x, y)) set_pixel(x, y, r, g, b);
      draw_framebuffer();
      y++;
    }

    step++;

    for (int i = 0; i < step; i++)
    {
      if (is_coordinate_on_screen(x, y)) set_pixel(x, y, r, g, b);
      draw_framebuffer();
      x--;
    }

    for (int i = 0; i < step; i++) {
      if (is_coordinate_on_screen(x, y)) set_pixel(x, y, r, g, b);
      draw_framebuffer();
      y--;
    }

    step++;
  }
}

/**
  * @brief  Draws snake pattern going in and out.
  * @retval None
  */
void draw_snake_go_in_out(void)
{
  draw_snake_pattern_in(1, 1, 0);
  draw_snake_pattern_out(0, 0, 0);
}

/**
  * @brief  Draws an example "W" bitmap on the screen.
  * @retval None
  */
void draw_W_bitmap(void)
{
  draw_rgb565_bitmap(W);
}
