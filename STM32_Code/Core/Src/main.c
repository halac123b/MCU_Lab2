/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7Seg(int num);
void configLedSystem(int state);
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DOT_Pin|LED_RED_Pin|EN0_Pin|EN1_Pin
                          |EN2_Pin|EN3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DOT_Pin LED_RED_Pin EN0_Pin EN1_Pin
                           EN2_Pin EN3_Pin */
  GPIO_InitStruct.Pin = DOT_Pin|LED_RED_Pin|EN0_Pin|EN1_Pin
                          |EN2_Pin|EN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_A_Pin SEG_B_Pin SEG_C_Pin SEG_D_Pin
                           SEG_E_Pin SEG_F_Pin SEG_G_Pin */
  GPIO_InitStruct.Pin = SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7Seg(int num){
	switch (num){
		case 0:{ // display 0 using leds: a, b, c, d, e, f
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_B_Pin | SEG_C_Pin |
									SEG_D_Pin | SEG_E_Pin | SEG_F_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, 1);
			break;
		}
		case 1:{ // display 1 using leds: b, c
			HAL_GPIO_WritePin(GPIOB, SEG_B_Pin | SEG_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_D_Pin | SEG_E_Pin |
									SEG_F_Pin | SEG_G_Pin, 1);
			break;
		}
		case 2:{ // display 2 using leds: a, b, d, e, g
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_B_Pin | SEG_D_Pin |
									SEG_E_Pin | SEG_G_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_C_Pin | SEG_F_Pin, 1);
			break;
		}
		case 3:{ // display 3 using leds: a, b, c, d, g
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_B_Pin | SEG_C_Pin |
									SEG_D_Pin | SEG_G_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_E_Pin | SEG_F_Pin, 1);
			break;
		}
		case 4:{ // display 4 using leds: b, c, f, g
			HAL_GPIO_WritePin(GPIOB, SEG_B_Pin | SEG_C_Pin | SEG_F_Pin |
									SEG_G_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_D_Pin | SEG_E_Pin, 1);
			break;
		}
		case 5:{ // display 5 using leds: a, c, d, f, g
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_C_Pin | SEG_D_Pin |
									SEG_F_Pin | SEG_G_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_B_Pin | SEG_E_Pin, 1);
			break;
		}
		case 6:{ // display 6 using leds: a, c, d, e, f, g
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_C_Pin | SEG_D_Pin |
									SEG_E_Pin | SEG_F_Pin | SEG_G_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, 1);
			break;
		}
		case 7:{ // diplay 7 using leds: a, b, c
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_B_Pin | SEG_C_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_D_Pin | SEG_E_Pin | SEG_F_Pin |
									SEG_G_Pin, 1);
			break;
		}
		case 8:{ // display 8 using leds: a, b, c, d, e, f, g
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_B_Pin | SEG_C_Pin |
									SEG_D_Pin | SEG_E_Pin | SEG_F_Pin |
									SEG_G_Pin, 0);
			break;
		}
		case 9:{ // display 9 using leds: a, b, c, d, f, g
			HAL_GPIO_WritePin(GPIOB, SEG_A_Pin | SEG_B_Pin | SEG_C_Pin |
									SEG_D_Pin | SEG_F_Pin | SEG_G_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, 1);
			break;
		}
	}
}

void configLedSystem(int state){ //config display for each 7seg led.
	switch(state){
		case 0:{ //display 1 for 7seg led 0
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, RESET);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN2_Pin | EN3_Pin, SET);
			display7Seg(1);
			break;
		}
		case 1:{ //display 2 for 7seg led 1
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, RESET);
			HAL_GPIO_WritePin(GPIOA, EN2_Pin | EN3_Pin | EN0_Pin, SET);
			display7Seg(2);
			break;
		}
		case 2:{ //display 3 for 7seg led 2
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, RESET);
			HAL_GPIO_WritePin(GPIOA, EN3_Pin | EN0_Pin | EN1_Pin, SET);
			display7Seg(3);
			break;
		}

		case 3:{ //display 0 for 7seg led 3
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, RESET);
			HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN2_Pin, SET);
			display7Seg(0);
			break;
		}
		default: break;
	}
}

int count = 50; // Each 7seg led frequency: 1/(50*10ms) = 2Hz
int count_led = 100; // PA5 Led Red and dot led frequency: 1/(100*10ms) = 1Hz
int state = 0; //0: Led 0 ON [display 1] - 1: Led 1 ON [display 2] - 2: Led 2 ON [display 3] - 3 Led 3 ON [display 0]
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (count > 0){ // timer for led 7 display system
		count--;
		if (count <= 0){ //config display for relevant 7-seg led
			count = 50;
			//TODO
			configLedSystem(state);
			state = (state +1) % 4; //limit range of state in [0..3]
		}
	}

	if (count_led > 0){ // timer for blinking led red PA5 and dot
		count_led--;
		if (count_led <= 0){ //toggle PA5 red led and dot led
			count_led = 100;
			//TODO
			HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin);
			HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
		}
	}
}
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

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/