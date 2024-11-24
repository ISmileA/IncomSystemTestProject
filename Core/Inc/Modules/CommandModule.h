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
#include "Modules/UsartModule.h"

#define BOOT_PIN	GPIO_PIN_15
#define RESET_PIN	GPIO_PIN_14
#define BOOT_PORT	GPIOC
#define RESET_PORT	GPIOC

#define AN_OK	0x01
#define AN_ERROR 0x00

void BootModeStart(){
	HAL_GPIO_WritePin(BOOT_PORT, BOOT_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
}

void BootModeEnd(){
	HAL_GPIO_WritePin(BOOT_PORT, BOOT_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
}

uint8_t AwaitResponce(uint8_t status, uint32_t maxWaitTime){
	uint32_t timer = HAL_GetTick();
	while(action.flag != status){
		if((HAL_GetTick()-timer) >= maxWaitTime || action.flag == NACK)
			return AN_ERROR;
	}
	return AN_OK;
}

void StartCommand(){

	uint8_t data[1] = {START_COMMAND};
	uint32_t timer = 0;
	while(action.flag == NONE){
	  if((HAL_GetTick()-timer) >= 1000){
		  TransmitOnAN3155(data, 1);
		  timer = HAL_GetTick();
	  }
	}
	action.flag = NONE;
	HAL_Delay(200);

}

uint8_t ReadFlashData(uint32_t address, uint16_t len){
	uint8_t data[5] = {READ_COMMAND, 0xFF^READ_COMMAND, 0, 0, 0};
	TransmitOnAN3155(data, 2);
	if(AwaitResponce(ACK, ANSWER_WAIT_TIME) == AN_ERROR)
		return AN_ERROR;
	action.flag = NONE;

	data[0] = (uint8_t)(address >> 24);
	data[1] = (uint8_t)(address >> 16);
	data[2] = (uint8_t)(address >> 8);
	data[3] = (uint8_t)(address);
	data[4] = crcAN3155(data, 4);
	TransmitOnAN3155(data, 5);
	if(AwaitResponce(ACK, ANSWER_WAIT_TIME) == AN_ERROR)
		return AN_ERROR;
	action.flag = NONE;

	data[0] = (uint8_t)(len-1);
	data[1] = ((uint8_t)(len-1))^0xFF;
	recive.command = RECIVE_DATA;
	recive.length = len+1;
	TransmitOnAN3155(data, 2);
	if(AwaitResponce(DATA, ANSWER_WAIT_TIME) == AN_ERROR)
		return AN_ERROR;
	recive.command = RECIVE_STATE;
	recive.length = 1;

	return AN_OK;
}

uint8_t GoInProgramm(uint32_t address){
	uint8_t data[5] = {GO_COMMAND, 0xFF^GO_COMMAND, 0, 0, 0};
	TransmitOnAN3155(data, 2);
	if(AwaitResponce(ACK, ANSWER_WAIT_TIME) == AN_ERROR)
		return AN_ERROR;
	action.flag = NONE;

	data[0] = (uint8_t)(address >> 24);
	data[1] = (uint8_t)(address >> 16);
	data[2] = (uint8_t)(address >> 8);
	data[3] = (uint8_t)(address);
	data[4] = crcAN3155(data, 4);
	TransmitOnAN3155(data, 5);
	if(AwaitResponce(ACK, ANSWER_WAIT_TIME) == AN_ERROR)
		return AN_ERROR;
	action.flag = NONE;
	return AN_OK;
}


#endif /* INC_COMMANDMODULE_H_ */
