#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "Modules/CommandModule.h"

extern UART_HandleTypeDef huart1;
uint8_t rxcall = 0;
ReciveData recive = {RECIVE_STATE, 1};
Action action = {GET_DATA_SIZE, 0, {}};
void SystemClock_Config(void);

uint32_t byteReads = 0;
uint32_t dataSize = 18428;
uint16_t crc16_schet = 0x3E42;
uint16_t crc_now = 0xFFFF;
uint16_t read = MAX_DATA;

uint16_t schet = 0;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  HAL_UART_Receive_IT(&huart1,&rxcall,1);

  BootModeStart();
  HAL_Delay(700);
  StartCommand();

  while (1)
  {
	  switch(action.command){
	  	  case(GET_DATA_SIZE):
			  if(ReadFlashData(FLASH_DATA_SIZE_POS, FLASH_DATA_SIZE_LEN)){
//				  dataSize = (uint32_t)(action.data[0] << 24) |
//			      (uint32_t)(action.data[1] << 16) | (uint32_t)(action.data[2] << 8) |
//				  (uint32_t)(action.data[3]);
//				  crc_now = crc16(crc_now, action.data, 2);
//				  uint8_t dt[2] = {action.data[2], action.data[3]};
//				  crc_now = crc16(crc_now, dt, 2);
				  action.command = GET_CRC16;
			  }
		  	  break;
	  	  case(GET_CRC16):
			  if(ReadFlashData(FLASH_CRC16_POS, 2)){
				  crc16_schet = (uint16_t)(action.data[0] << 8) |
				  (uint16_t)(action.data[1]);
				  action.command = READ_DATA;
			  }
	  	  	  break;
	  	  case(READ_DATA):
			  if(ReadFlashData(FLASH_ADRESS_START+byteReads, read) && dataSize >= read){
				  byteReads+=read;
				  crc_now = crc16(crc_now, action.data, read);
				  schet+=1;
				  if((dataSize-byteReads) == 0){
					  HAL_GPIO_WritePin(BOOT_PORT, BOOT_PIN, GPIO_PIN_RESET);
					  action.command = GO_COMMAND;
				  }else if((dataSize-byteReads) < read){
					  read = (dataSize-byteReads);
				  }
			  }
	  	  	  break;
	  	  case(GO_COMMAND):
			  if(GoInProgramm(0x80000000)){
				  action.command = 0x00;
			  }
	  	  	  break;
	  	  case(0):
			  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			  HAL_Delay(500);
	  }
  }
}

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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}
