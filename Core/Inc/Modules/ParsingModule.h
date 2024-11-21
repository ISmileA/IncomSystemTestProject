/*
 * ParsingModule.h
 *
 *  Created on: Nov 21, 2024
 *      Author: arsen
 */

#ifndef INC_MODULES_PARSINGMODULE_H_
#define INC_MODULES_PARSINGMODULE_H_

#include "main.h"

void DataParser(uint8_t *data){
	switch(recive.command){
		case(RECIVE_STATE):
			if(data[0] == ACK){
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				action.state++;
				action.flag = 1;
			}else
			break;
		case(RECIVE_DATA):
			action.flag = 1;
			action.state++;
			break;
	}
}

#endif /* INC_MODULES_PARSINGMODULE_H_ */
