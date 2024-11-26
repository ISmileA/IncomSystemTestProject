#include "Modules/UsartModule.h"
#include "Modules/ParsingModule.h"

uint16_t recived_bytes = 0;
uint8_t buffer[1024] = {};
uint32_t timer = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if((HAL_GetTick()-timer) >= 5)
		recived_bytes = 0;
	buffer[recived_bytes] = rxcall;
	recived_bytes++;
	if(recived_bytes == recive.length){
		recived_bytes = 0;
		DataParser(buffer);
	}
	timer = HAL_GetTick();
	HAL_UART_Receive_IT(huart,&rxcall,1);
}

void TransmitOnAN3155(uint8_t *data, uint16_t len){
	for (uint16_t i = 0; i<len; i++){
		USART1->DR = data[i];
//		while ((USART1->SR & USART_SR_TXE) == 0);
		HAL_Delay(1);
	}
}
