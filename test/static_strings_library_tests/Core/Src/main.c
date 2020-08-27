/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
  static_strings_init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  //test 1

  uint8_t very_long_string[700];
  uint16_t i;
  for(i = 0; i < 699; i++){
	  very_long_string[i] = 'a';
  }
  very_long_string[699] = '\0';
  static_strings_string_descriptor *very_long_string_descriptor = static_strings_save(very_long_string);
  char length[6];
  sprintf(length,"%04d",very_long_string_descriptor->length);
  length[4] = '\r';
  length[5] = '\n';
  HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
  char type[3];
  type[0] = very_long_string_descriptor->type + 48;
  type[1] = '\r';
  type[2] = '\n';
  HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart1,(uint8_t *)very_long_string_descriptor->string,very_long_string_descriptor->length,HAL_MAX_DELAY);

  static_strings_deallocate(very_long_string_descriptor);

  uint8_t test_very_short_strings[10][50] = {"rapmr\r\n","ejkxjde7wp\r\n","rmp642c8un8bcjj\r\n","5ynn4y8caurm3trzwq4j\r\n","hwcqtzcn4gc8avg4d4zi7nr9f\r\n","tgt62yw9jnugwbg3pgzax73z6uix7g\r\n","bwn8czmxkhexdiw77v4gk4xu2yqtqibv2jn\r\n","eykku6i7j36kewjbwvpd5x9viggdhreqe9amk7ub\r\n","mpjkqkrn22q4xzvpt897fwjjurgtj3vczmmhy64d8qgww\r\n","wgxfec343aaku5axbjt5w2e5cz63r9bbydqun88ukj9iwint\r\n"};
  uint8_t test_short_strings[6][100] = {"b6cwufw3yyfz4kdxmpmjbt8p5kq43m8hynkanabtjrgrc4iitx8tvdbkgima\r\n","j85npdf3rjtf8egmja2cxuqgu6z4h38ikaue7evfqytbuw5b95pjmqvnhejmjkc8c\r\n","bduzvngtikgxbm2wc4wrwq75ti4c5cvavcna7k4cur4mi56gegbfnc5jd6i484efri9ddh\r\n","44upv7qtmzngmbp7gdbfnumhx82iwpz8vtp9dd7vyq4yn56jqfj7g5pd44gxg9t5tw466u6gbum\r\n","5gpxtjyj79j438uif2ukmyj67v5hebnh45tpaxa9cc92t28nwct2hghqb7kf96vrzz9dqj6hcfqtjfyi\r\n","e7gbz5rqwhmr3bq6jfuav9hgya8fthpi4jn6yiwgd5hmv9mjke8r8eva7dbzyr2pn9wavx386u6dnj6zdkerc\r\n"};
  uint8_t test_medium_strings[2][200] = {"27wnc489rtjak6963r7c8mw4zmm7nxkhneu9wbg6nemurramx4yx6zipi2kmjh3n9hr6aci9dcku5w87ez8fkr5fnuzdk8q74ekkwgfnm3kq7dk82d24vujdpupp83rbfw5bnci7h5zx6iuzadukvc\r\n","ieckbpek2tuq837haz8cy78dpki9eav589t2bx5ffkx44kcj9tw5hwqyfqwgi5mjrww2i39jg9hz7djdddyp3b6uyy69cniwzeu8y4kgv2xmkji97dpxcfhr\r\n"};
  uint8_t test_long_string[500] = "2j97e72cutbnqwcc4rg6rvqniyravzyqj4k7ee44pwvwmi2kvdk3vmmbr7396q7uajqmukehfn7qhr9pj4k974wbiw6dxr9ckmmj4bnkd5ndxn6ia27rjyyhdnrgk2kgdrqfhkeq8jwdz9rgd6wyw52yqxz5v873j7q9gc3bwfmiv6deutkj7fvvg8m877tgtnq5a5ueqd589prwfk5ex7bjixicnhb3x9n9m5vqtpbtgzx4vvbc9jcqrpfbgxjpvawrkeyjkk7aifkfr6xjerkxz7bk6cekpqttf72788m23qaz7xncba4g8dvayzwqqyev6ie3dgyfyew2rew6nba9nte3p5\r\n";
  uint8_t test_very_long_string[1000] = "3ghgwfrwyrzzdhr2929pnvm7ht4bgvq6bii7cz7ajp98475pgbwt3tww7prn86y7e6gdhvda923y4wzu5xwex9a8ntjf243h94z848k9fhym39qrt8ypp9rcge8drmxfeb9bn5mryc738w2mdk8weyxnti2zy9a7j3w7947qhce3bvv5d8yjxxt7ncik4muju5zcqzab5vf2wvz49w3j8v23u3grci33hdxvniy7h2p2r4b4xig3j5nfnn6m2qvmw5b5hzii32mrh7ebr2tuaqgdxn8xbecjpnvpv7timpd7cpqyubdjczaftwrrum8bdtfqzp4wr8him9n3g4nc347f264jhzb7w6bmyh9gj3zwrau6czz67ybq2cdh6p7cdbyvk88u5rfh9xi3u6fgbzfnu9b9qv6kd4mxhc6t758tad8n4i396qw2v3r2th3dag8d7h837ibpdx8v8njvkg7dh9j5rqmnvktcegmtxaprhxky8f6ppwcgeei29a6z3inht7kzm9x62muqc6cijrzfqm3yvukurwge4mi5fnzb5gqbz279kbpzy484ndrc2vrczwa2zmvjvdad39vjtwqp\r\n";

  static_strings_string_descriptor *string_descriptor;

  //test 2

  string_descriptor = static_strings_save(test_very_long_string);
  sprintf(length,"%04d",string_descriptor->length);
  length[4] = '\r';
  HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
  type[0] = string_descriptor->type + 48;
  HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);

  //test 3

  string_descriptor = static_strings_save(test_long_string);
  sprintf(length,"%04d",string_descriptor->length);
  length[4] = '\r';
  HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
  type[0] = string_descriptor->type + 48;
  HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);

  //test 4,5

  for(i = 0; i < 2; i++){
  	  string_descriptor = static_strings_save(test_medium_strings[i]);
  	  sprintf(length,"%04d",string_descriptor->length);
  	  length[4] = '\r';
  	  HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
  	  type[0] = string_descriptor->type + 48;
  	  HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
  	  HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);
  }

  //test 6-11

  for(i = 0; i < 6; i++){
  	  string_descriptor = static_strings_save(test_short_strings[i]);
  	  sprintf(length,"%04d",string_descriptor->length);
  	  length[4] = '\r';
  	  HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
  	  type[0] = string_descriptor->type + 48;
  	  HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
  	  HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);
  }

  //test 12-21

  static_strings_string_descriptor *string_descriptor_deallocate = NULL;
  for(i = 0; i < 10; i++){
	  string_descriptor = static_strings_save(test_very_short_strings[i]);
	  if(i == 6){
		  string_descriptor_deallocate = string_descriptor;
	  }
	  sprintf(length,"%04d",string_descriptor->length);
	  length[4] = '\r';
	  HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
	  type[0] = string_descriptor->type + 48;
	  HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
	  HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);
  }

  //test 22

  static_strings_deallocate(string_descriptor_deallocate);
  uint8_t test_short_string[50] = "reallocate_test\r\n";
  string_descriptor = static_strings_save(test_short_string);
  sprintf(length,"%04d",string_descriptor->length);
  length[4] = '\r';
  HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
  type[0] = string_descriptor->type + 48;
  HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);

  //test 23

  uint8_t pointer[12];
  sprintf((char *)pointer,"%10p",string_descriptor_deallocate);
  pointer[10] = '\r';
  pointer[11] = '\n';
  HAL_UART_Transmit(&huart1,pointer,12,HAL_MAX_DELAY);

  sprintf((char *)pointer,"%10p",string_descriptor);
  pointer[10] = '\r';
  pointer[11] = '\n';
  HAL_UART_Transmit(&huart1,pointer,12,HAL_MAX_DELAY);

  uint8_t error_code_char;

  //test 24

  uint8_t no_memory_string[800];
  for(i = 0; i < 798; i++){
	  no_memory_string[i] = 'a';
  }
  no_memory_string[798] = '\r';
  no_memory_string[799] = '\n';
  string_descriptor = static_strings_save(no_memory_string);
  if(string_descriptor == NULL){
	  error_code_char = static_strings_error_code + 48;
  }
  else{
	  error_code_char = '3';
  }
  HAL_UART_Transmit(&huart1,&error_code_char,1,HAL_MAX_DELAY);

  //test 25

  uint8_t unallocable_invalid_string[1200];
  for(i = 0; i < 1198; i++){
	  unallocable_invalid_string[i] = 'a';
  }
  unallocable_invalid_string[1198] = '\r';
  unallocable_invalid_string[1199] = '\n';
  string_descriptor = static_strings_save(unallocable_invalid_string);
  if(string_descriptor == NULL){
	  error_code_char = static_strings_error_code + 48;
  }
  else{
	  error_code_char = '4';
  }
  HAL_UART_Transmit(&huart1,&error_code_char,1,HAL_MAX_DELAY);

  //test 26

  uint8_t no_line_end_invalid_string[800];
  for(i = 0; i < 800; i++){
	  no_line_end_invalid_string[i] = 'a';
  }
  string_descriptor = static_strings_save(no_line_end_invalid_string);
  if(string_descriptor == NULL){
	  error_code_char = static_strings_error_code + 48;
  }
  else{
	  error_code_char = '5';
  }
  HAL_UART_Transmit(&huart1,&error_code_char,1,HAL_MAX_DELAY);

  //test 27

  string_descriptor = static_strings_allocate(1200);
  if(string_descriptor == NULL){
  	  error_code_char = static_strings_error_code + 48;
  }
  else{
  	  error_code_char = '6';
  }
  HAL_UART_Transmit(&huart1,&error_code_char,1,HAL_MAX_DELAY);

  //test 28

  uint8_t custom[10] = "123,56,89\0";
  static_strings_string_descriptor custom_string_descriptor;
  string_descriptor = &custom_string_descriptor;
  static_strings_create_custom_string(string_descriptor,custom);
  HAL_UART_Transmit(&huart1,string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);

  // test 29

  if(static_strings_is_line(string_descriptor)){
	  HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
  }
  else{
	  HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
  }

  // test 30

  uint8_t custom_line[10] = "123,56,8\r\n";
  static_strings_create_custom_string(string_descriptor,custom_line);

  if(static_strings_is_line(string_descriptor)){
	  HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
  }
  else{
	  HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
  }

  // test 31-33

  static_strings_string_descriptor token;
  static_strings_string_splitter_set_parameters(string_descriptor,',');
  while(static_strings_string_splitter_get_next_token(&token)){
	  HAL_UART_Transmit(&huart1,token.string,token.length,HAL_MAX_DELAY);
  }

  // test 34

  int next_token_result = static_strings_string_splitter_get_next_token(&token);
  if(next_token_result){
	  HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
  }
  else{
	  HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
  }

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
  huart1.Init.BaudRate = 115200;
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
