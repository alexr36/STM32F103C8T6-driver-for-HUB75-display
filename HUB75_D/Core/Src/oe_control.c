// -----------------------------------------------------------------------------
// Includes
// -----------------------------------------------------------------------------
#include "tim.h"
#include "stm32f1xx_hal_gpio.h"

// -----------------------------------------------------------------------------
// Output Enable (OE) pin manipulation functions
// -----------------------------------------------------------------------------

/**
  * @brief  Initializes TIM3 on Channel 3.
  * @retval None
  */
void OE_PWM_Init(void)
{
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

/**
  * @brief  Sets brightness of LED diodes using Output Enable (OE) pin (by PWM).
  * @param  brightness_percent: Percent of brightness to set (0-100)
  * @retval None
  */
void OE_set_brightness(uint8_t brightness_percent)
{
  if (brightness_percent > 100) brightness_percent = 100;

  uint32_t period = __HAL_TIM_GET_AUTORELOAD(&htim3);
  uint32_t pulse = ((100 - brightness_percent) * period) / 100;

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pulse);
}
