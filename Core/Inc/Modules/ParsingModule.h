/*
 * ParsingModule.h
 *
 *  Created on: Nov 21, 2024
 *      Author: ISmileA
 */

#ifndef INC_MODULES_PARSINGMODULE_H_
#define INC_MODULES_PARSINGMODULE_H_

#include "main.h"

void DataParser(uint8_t *data){
	switch(recive.command){
		case(RECIVE_STATE):
			action.flag = data[0];
			break;
		case(RECIVE_DATA):
		    for(uint16_t i=0; i<recive.length-1; i++){
		    	action.data[i] = data[i+1];
		    }
			action.flag = DATA;
			break;
	}
}

#endif /* INC_MODULES_PARSINGMODULE_H_ */
