#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "Modules/ActionModule.h"
#include "Inits/RCCInit.h"

extern UART_HandleTypeDef huart1;
uint8_t rxcall = 0;
ReciveData recive = {RECIVE_STATE, 1};
Action action = {GET_DATA_SIZE, 0, {}};

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  HAL_UART_Receive_IT(&huart1,&rxcall,1);

  BootModeStart(); 								// Start boot mode
  HAL_Delay(400);

  StartCommand();  								// Start connection
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
  while (1)
  {
	  switch(action.command){
	  	  case(GET_DATA_SIZE):
			  GetDataSize(FLASH_DATA_SIZE_POS);
		  	  break;
	  	  case(GET_CRC16):
			  GetCrc16(FLASH_CRC16_POS);
	  	  	  break;
	  	  case(READ_DATA):
			  ReadMemoryOnDevice();
	  	  	  break;
	  	  case(GO_COMMAND):
			  VerifyAndGo();
	  	  	  break;
	  	  case(SUCCESS_LOG):
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	  	  	  break;
	  	  case(ERROR_LOG):
			  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			  HAL_Delay(500);
	  }
  }
}
