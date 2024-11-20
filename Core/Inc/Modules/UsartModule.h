/*
 * UsartModule.h
 *
 *  Created on: Nov 20, 2024
 *      Author: arsen
 */

#ifndef MODULES_USARTMODULE_H_
#define MODULES_USARTMODULE_H_

#include "main.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_UART_Receive_IT(huart,&rxcall,1);
}


#endif /* MODULES_USARTMODULE_H_ */
