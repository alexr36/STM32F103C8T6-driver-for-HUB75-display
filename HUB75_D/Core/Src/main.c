/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hub75.h"
#include "oe_control.h"
#include "utils.h"
#include "examples.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  OE_PWM_Init();

  clear_framebuffer();
  //OE_set_brightness(5);
  draw_test_cross();
  //draw_W_bitmap();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	screen_fade(95);


	  // 2 piksele pod sobą
//	  clear_framebuffer();
//	  set_pixel(4, 0, 1, 0, 0);   // powinna zapalić się linia 0 (panel 1)
//	  set_pixel(4, 16, 0, 1, 0);  // powinna zapalić się linia 0 (panel 2)
//	  set_pixel(4, 1, 1, 0, 1);   // powinna zapalić się linia 1 (panel 1)
//	  set_pixel(4, 17, 0, 0, 1);  // powinna zapalić się linia 1 (panel 2)
//	  draw_framebuffer();


	  // Spadające piksele
//	  for (int i = 0; i < 10; i++) draw_framebuffer();
//
//	  clear_framebuffer();
//
//	  // Piksel w górnym panelu (R1) — rząd 0–15
//	  set_pixel(4, test_row, 1, 0, 0);  // czerwony
//
//	  // Piksel w dolnym panelu (R2) — rząd 16–31
//	  set_pixel(8, test_row, 0, 1, 0);  // zielony
//
//	  draw_framebuffer();
//
//	  test_row = (test_row + 1) /*% 32*/;  // przechodź przez 0..15
//	  if (test_row == 64) test_row = 0;
//	  HAL_Delay(10);


	  // Spadające paski
//	  clear_framebuffer();
//
//	  // Panel 1 (upper): starting from y = 10
//	  for (uint8_t x = 0; x < 64; x++) {
//	      set_pixel(x, (10 + offset1) % 32, 1, 0, 0);
//	  }
//
//	  // Panel 2 (lower): starting from y = 42 (10 + 32)
//	  for (uint8_t x = 0; x < 64; x++) {
//	      set_pixel(x, (10 + offset2) % 32 + 32, 0, 1, 0);
//	  }
//
//	  /*for (int i = 0; i < 10; i++)*/ draw_framebuffer();
//
//
//	  offset1 = (offset1 + 1) % 32;
//	  offset2 = (offset2 + 2) % 32;  // different speed
//
//	  HAL_Delay(1);



//	  while (CH3_DC < 65535)
//	  {
//	     TIM3->CCR1 = CH3_DC;
//	     CH3_DC += 70;
//	     HAL_Delay(1);
//	  }
//	  while (CH3_DC > 0)
//	  {
//	     TIM3->CCR1 = CH3_DC;
//	     CH3_DC -= 70;
//	     HAL_Delay(1);
//	  }
//	  for (uint8_t rot = 0; rot < 4; rot++)
//	  {
//	    draw_rotated_cross(rot);
//	    for (int i = 0; i < 50; i++) {
//	      draw_framebuffer();  // odświeżenie
//	      HAL_Delay(20);       // kontrola prędkości animacji
//	    }
//	  }


	  //screen_fade(100);
	  //draw_snake_pattern(1, 0, 1);
	  //draw_snake_pattern_center_out(0, 0, 0);
	  //snake_go_in_out();

//	    draw_framebuffer();
//
//	    OE_set_brightness(brightness);
//	    HAL_Delay(1);
//
//	    brightness += dir;
//	    if (brightness == 100 || brightness == 10) dir = -dir;



//	  // Test własny rgb
//	  clear_framebuffer();
//	  set_pixel(63, 16, 1, 0, 0);
//
//	  set_pixel(4, 29, 1, 0, 0);  // r
//	  set_pixel(5, 30, 0, 1, 0);  //  g
//	  set_pixel(6, 31, 0, 0, 1);  //   b
//	  draw_framebuffer();
//	  HAL_Delay(100);


	  // Zapalane rzędy
//	  output_enable(0);
//	  set_row(0); // tylko rząd 0
//	  HAL_GPIO_WritePin(PORT_A, R1_PIN, GPIO_PIN_SET); // zapal R1
//      HAL_GPIO_WritePin(PORT_A, R2_PIN, GPIO_PIN_SET); // zapal R2
//	  for (int i = 0; i < 64; i++) clock_pulse();
//	  latch_data();
//	  output_enable(1);
//	  HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
