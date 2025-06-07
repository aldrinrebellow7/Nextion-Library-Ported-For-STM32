/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "../libraries/Nextion/Nextion.h"
#include <string>
#include <string.h>
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
 UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define ROWS 5
#define COLS 5
#define NAME_LENGTH 20
#define DATE_LENGTH 20
#define TEMP_LENGTH 100

static int row_table = 0;
static bool table_first_boot = false;
struct Data {
  int serialNumber;
  char date[DATE_LENGTH];
  char name[NAME_LENGTH];
  int value;
} data[ROWS][COLS] = {
  {{1, "01/01/2021", "John Smith", 100}, {2, "01/02/2021", "Jane Doe", 200}, {3, "01/03/2021", "Bob Johnson", 300}, {4, "01/04/2021", "Emily Davis", 400}, {5, "01/05/2021", "Michael Brown", 500}},
  {{6, "02/01/2021", "Emily Wilson", 600}, {7, "02/02/2021", "Joshua Moore", 700}, {8, "02/03/2021", "Daniel Thompson", 800}, {9, "02/04/2021", "Matthew White", 900}, {10, "02/05/2021", "Jacob Harris", 1000}},
  {{11, "03/01/2021", "Nicholas Martin", 1100}, {12, "03/02/2021", "William Thompson", 1200}, {13, "03/03/2021", "Amanda Gomez", 1300}, {14, "03/04/2021", "Ashley Martin", 1400}, {15, "03/05/2021", "Brian Anderson", 1500}},
  {{16, "04/01/2021", "Brandon Lee", 1600}, {17, "04/02/2021", "Adam Lewis", 1700}, {18, "04/03/2021", "Gabriel Hall", 1800}, {19, "04/04/2021", "Benjamin Allen", 1900}, {20, "04/05/2021", "Nicholas Young", 2000}},
  {{21, "05/01/2021", "Jacob Scott", 2100}, {22, "05/02/2021", "Ryan Green", 2200}, {23, "05/03/2021", "Jacob Martinez", 2300}, {24, "05/04/2021", "Michael Perez", 2400}, {25, "05/05/2021", "David Thompson", 2500}}
};

void sendNextDataToTable(void) 
{

	if(true == table_first_boot)
	{
	    ++row_table;
	    if(row_table>=ROWS)
	    {
	    	row_table =ROWS-1;
	    }
	}
	else
	{
		table_first_boot = true;
	}
	sendCommand("data0.clear()");
    for (int col = COLS-1; col >= 0; col--)
    {
    	char temp[TEMP_LENGTH] = {0};
    	sprintf(temp, "va0.txt=\"%d^%s^%s^%d^\"", data[row_table][col].serialNumber, data[row_table][col].date, data[row_table][col].name, data[row_table][col].value);
    	sendCommand(temp);
    	sendCommand("t0.txt=va0.txt");
    	sendCommand("data0.insert(va0.txt)");
    }
}

void sendBackDataToTable(void) 
{

	if(true == table_first_boot)
	{
	    --row_table;
	    if(row_table<0)
	    {
	    	row_table =0;
	    }
	}
	else
	{
		table_first_boot = true;
	}
	sendCommand("data0.clear()");
	for (int col = COLS-1; col >= 0; col--)
    {
    	char temp[TEMP_LENGTH] = {0};
    	sprintf(temp, "va0.txt=\"%d^%s^%s^%d^\"", data[row_table][col].serialNumber, data[row_table][col].date, data[row_table][col].name, data[row_table][col].value);
    	sendCommand(temp);
    	sendCommand("t0.txt=va0.txt");
    	sendCommand("data0.insert(va0.txt)");
    }

}

NexDSButton bt0 = NexDSButton(0, 1, "bt0");
NexDSButton bt1 = NexDSButton(0, 1, "bt1");
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  nexInit(&huart1, 9600/*Baudrate*/);/*Initilize Nex library with huart1 as UART interface*/

  NexCrop q0 = NexCrop(0, 1, "q0");
  (void)q0;
  NexGauge pointer  = NexGauge(0, 1, "pointer");
  (void)pointer;
  NexHotspot hot0    = NexHotspot(0, 1, "hot0");
  (void)hot0;
  NexPage page0    = NexPage(0, 0, "page0");
  (void)page0;
  NexPicture p0 = NexPicture(0, 1, "p0");
  (void)p0;
  NexProgressBar j0  = NexProgressBar(0, 3, "j0");
  (void)j0;
  NexSlider h0 = NexSlider(0, 1, "h0");
  (void)h0;
  NexText t0 = NexText(0, 2, "t0");
  (void)t0;
  NexWaveform s0 = NexWaveform(0, 1, "s0");
  (void)s0;
  NexTimer tm0 = NexTimer(0, 1, "tm0");
  (void)tm0;
  NexNumber n0 = NexNumber(0, 3, "n0");
  (void)n0;
  NexGpio gpio;
  (void)gpio;
  NexRtc  rtc;
  (void)rtc;
  sendNextDataToTable();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    uint32_t dual_state = 0;
    bt1.getValue(&dual_state);
    if(dual_state)
    {
      sendNextDataToTable();
      sendCommand("bt1.val=0");
      sendCommand("bt0.val=0");
    }
    dual_state = 0;
    bt0.getValue(&dual_state);
    if(dual_state)
    {
      sendBackDataToTable();
      sendCommand("bt0.val=0");
      sendCommand("bt1.val=0");
    }
    HAL_Delay(500);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
