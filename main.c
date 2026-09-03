/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

uint8_t datoUART;

uint8_t SeAc = 0;
uint8_t JAc = 0;

/* Jugador 1*/
uint8_t contadorJ1 = 0;
uint32_t tJ1 = 0;

/* Jugador 2*/
uint8_t contadorJ2 = 0;
uint32_t tJ2 = 0;

/* Ganador */
uint32_t ganador = 0;


#define t_antir 200

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void semaforo(void);
void mostrarNumero1(uint8_t numero);
void mostrarNumero2(uint8_t numero);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* Mostrar números del contador de décadas del Jugador 1 */

void mostrarNumero1(uint8_t numero)
{
    /* Apagado */
    HAL_GPIO_WritePin(J1LED1_GPIO_Port, J1LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(J1LED2_GPIO_Port, J1LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(J1LED3_GPIO_Port, J1LED3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(J1LED4_GPIO_Port, J1LED4_Pin, GPIO_PIN_RESET);

    /* Muestra número */
    switch(numero)
    {
        case 0:
            /* 0000 */
            break;
        case 1:
            /* 0001 */
            HAL_GPIO_WritePin(J1LED1_GPIO_Port, J1LED1_Pin, GPIO_PIN_SET);
            break;
        case 2:
            /* 0010 */
            HAL_GPIO_WritePin(J1LED2_GPIO_Port, J1LED2_Pin, GPIO_PIN_SET);
            break;
        case 3:
            /* 0100 */
            HAL_GPIO_WritePin(J1LED3_GPIO_Port, J1LED3_Pin, GPIO_PIN_SET);
            break;
        case 4:
            /* 1000 */
            HAL_GPIO_WritePin(J1LED4_GPIO_Port, J1LED4_Pin, GPIO_PIN_SET);
            break;
        default:
            break;
    }
}



/* Mostrar números del contador de décadas del Jugador 2 */
void mostrarNumero2(uint8_t numero)
{
    /* Apagado */
    HAL_GPIO_WritePin(J2LED1_GPIO_Port, J2LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(J2LED2_GPIO_Port, J2LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(J2LED3_GPIO_Port, J2LED3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(J2LED4_GPIO_Port, J2LED4_Pin, GPIO_PIN_RESET);

    /* Muestra número */
    switch(numero)
    {
        case 0:
            /* 0000 */
            break;
        case 1:
            /* 0001 */
            HAL_GPIO_WritePin(J2LED1_GPIO_Port, J2LED1_Pin, GPIO_PIN_SET);
            break;
        case 2:
            /* 0010 */
            HAL_GPIO_WritePin(J2LED2_GPIO_Port, J2LED2_Pin, GPIO_PIN_SET);
            break;
        case 3:
            /* 0100 */
            HAL_GPIO_WritePin(J2LED3_GPIO_Port, J2LED3_Pin, GPIO_PIN_SET);
            break;
        case 4:
            /* 1000 */
            HAL_GPIO_WritePin(J2LED4_GPIO_Port, J2LED4_Pin, GPIO_PIN_SET);
            break;
        default:
            break;
    }
}


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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_UART_Receive_IT(&huart2, &datoUART, 1);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(SeAc == 1)
	      {
	          SeAc = 0;

	          /* Reiniciar carrera */
	          contadorJ1 = 0;
	          contadorJ2 = 0;
	          ganador = 0;

	          mostrarNumero1(contadorJ1);
	          mostrarNumero2(contadorJ2);

	          semaforo();
	      }

	      /* Enviar mensaje del ganador */
	      if(ganador == 1)
	      {
	          ganador = 0;

	          HAL_UART_Transmit(&huart2, (uint8_t*)"Jugador 1 gana!\r\n", 18, HAL_MAX_DELAY);
	      }
	      if(ganador == 2)
	      {
	          ganador = 0;

	          HAL_UART_Transmit(&huart2, (uint8_t*)"Jugador 2 gana!\r\n", 18, HAL_MAX_DELAY);
	      }

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, J2LED2_Pin|J2LED1_Pin|J1LED4_Pin|J1LED1_Pin
                          |LEDR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(J1LED2_GPIO_Port, J1LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LEDG_Pin|LEDY_Pin|J1LED3_Pin|J2LED4_Pin
                          |J2LED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : J2LED2_Pin J2LED1_Pin J1LED4_Pin J1LED1_Pin
                           LEDR_Pin */
  GPIO_InitStruct.Pin = J2LED2_Pin|J2LED1_Pin|J1LED4_Pin|J1LED1_Pin
                          |LEDR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BJ1_Pin */
  GPIO_InitStruct.Pin = BJ1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(BJ1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : J1LED2_Pin */
  GPIO_InitStruct.Pin = J1LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(J1LED2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BJ2_Pin */
  GPIO_InitStruct.Pin = BJ2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(BJ2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LEDG_Pin LEDY_Pin J1LED3_Pin J2LED4_Pin
                           J2LED3_Pin */
  GPIO_InitStruct.Pin = LEDG_Pin|LEDY_Pin|J1LED3_Pin|J2LED4_Pin
                          |J2LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


void semaforo(void)
{
    HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);

    HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);

    HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);

    HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_RESET);

    JAc = 1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)
    {
        if(datoUART == 'S' && JAc == 0 && SeAc == 0)
        {
            SeAc = 1;
        }

        /* Volver a escuchar UART */
        HAL_UART_Receive_IT(&huart2, &datoUART, 1);
    }
}

/* Interrupciones de los jugadores*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* Jugador 1 */
    if(GPIO_Pin == BJ1_Pin)
    {
        if(JAc == 1)
        {
            /* Anti-rebote */
            if((HAL_GetTick() - tJ1) >= t_antir)
            {
                if(contadorJ1 < 4)
                {
                    contadorJ1++;
                    mostrarNumero1(contadorJ1);
                    if(contadorJ1 == 4)
                    {
                        JAc = 0;
                        ganador = 1;
                    }
                }
                tJ1 = HAL_GetTick();
            }
        }
    }

    /* Jugador 2 */
    if(GPIO_Pin == BJ2_Pin)
    {
        if(JAc == 1)
        {
            /* Anti-rebote */
            if((HAL_GetTick() - tJ2) >= t_antir)
            {
                if(contadorJ2 < 4)
                {
                    contadorJ2++;
                    mostrarNumero2(contadorJ2);

                    if(contadorJ2 == 4)
                    {
                        JAc = 0;
                        ganador = 2;
                    }
                }
                tJ2 = HAL_GetTick();
            }
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
