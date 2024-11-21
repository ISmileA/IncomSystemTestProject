/*
 * CommandModule.h
 *
 *  Created on: Nov 20, 2024
 *      Author: arsen
 */

#ifndef INC_COMMANDMODULE_H_
#define INC_COMMANDMODULE_H_

#include "main.h"
#include "Configs/BootConfig.h"
#include "Modules/CrcModule.h"

#define BOOT_PIN	GPIO_PIN_14
#define RESET_PIN	GPIO_PIN_15
#define BOOT_PORT	GPIOC
#define RESET_PORT	GPIOC

static uint32_t timer = 0;

void BootModeStart(){
	HAL_GPIO_WritePin(BOOT_PORT, BOOT_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
}

void StartCommand(){
	switch(action.state){
		case(0):
			if((HAL_GetTick()-timer) >= ANSWER_WAIT_TIME){
				uint8_t data[1] = {START_COMMAND};
				recive.command = RECIVE_STATE;
				recive.length = 1;
				HAL_UART_Transmit_IT(&huart1, data, 1);
				timer = HAL_GetTick();
			}
			break;
		case(1):
			action.command = READ_COMMAND;
			action.state = 0;
			timer = 0;
	}
}

void TestRead(){
	uint8_t data[5] = {0, 0, 0, 0, 0};
	data[1] = 0xFF^data[0];
	HAL_UART_Transmit_IT(&huart1, data, 2);
//	while(action.flag == 0){}
//	action.flag = 0;
//	uint32_t startAdress = FLASH_ADRESS_START;
//	data[0] = (uint8_t)(startAdress >> 24);
//	data[1] = (uint8_t)(startAdress >> 16);
//	data[2] = (uint8_t)(startAdress >> 8);
//	data[3] = (uint8_t)(startAdress);
//	data[4] = crcAN3155(data, 4);
//	recive.command = RECIVE_STATE;
//	recive.length = 1;
//	HAL_UART_Transmit_IT(&huart1, data, 5);
//	while(action.flag == 0){}
//	action.flag = 0;
//	data[0] = 10;
//	data[1] = 0xFF^data[0];
//    recive.command = RECIVE_DATA;
//    recive.length = 10;
//    HAL_UART_Transmit_IT(&huart1, data, 2);
}

void ReadFlashData(uint32_t startAdress, uint8_t length){
		switch(action.state){
			case(0):
				if((HAL_GetTick()-timer) >= ANSWER_WAIT_TIME || action.flag){
					action.flag = 0;
					uint8_t data[2] = {READ_COMMAND, 0};
					data[1] = crcAN3155(data, 1);
					recive.command = RECIVE_STATE;
					recive.length = 1;
					HAL_UART_Transmit_IT(&huart1, data, 2);
					timer = HAL_GetTick();
				}
			case(1):
				if((HAL_GetTick()-timer) >= ANSWER_WAIT_TIME || action.flag){
					action.flag = 0;
					uint8_t data[5] = {};
					data[0] = (uint8_t)(startAdress >> 24);
					data[1] = (uint8_t)(startAdress >> 16);
					data[2] = (uint8_t)(startAdress >> 8);
					data[3] = (uint8_t)(startAdress);
					data[4] = crcAN3155(data, 4);
					recive.command = RECIVE_STATE;
					recive.length = 1;
					HAL_UART_Transmit_IT(&huart1, data, 5);
					timer = HAL_GetTick();
				}
			case(2):
			   if((HAL_GetTick()-timer) >= ANSWER_WAIT_TIME || action.flag){
				   action.flag = 0;
				   uint8_t data[2] = {length, 0};
				   data[1] = crcAN3155(data, 1);
				   recive.command = RECIVE_DATA;
				   recive.length = length;
				   HAL_UART_Transmit_IT(&huart1, data, 2);
				   timer = HAL_GetTick();
			   }
			case(3):
				action.flag = 0;
				action.state = 0;
				timer = 0;
				break;
		}
}


#endif /* INC_COMMANDMODULE_H_ */
