/*
 * CommandModule.c
 *
 *  Created on: Nov 26, 2024
 *      Author: ISmileA
 */

#include "Modules/CommandModule.h"
#include "Modules/UsartModule.h"

uint8_t AwaitResponce(uint8_t status, uint32_t maxWaitTime);
uint8_t crcAN3155(uint8_t *data, uint8_t len);


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
		if((HAL_GetTick()-timer) >= maxWaitTime)
			return AN_ERROR;
		else if(action.flag == NACK){
			action.command = ERROR_LOG;
			return AN_ERROR;
		}
	}
	return AN_OK;
}

uint8_t crcAN3155(uint8_t *data, uint8_t len){
	uint8_t numb = 0;
	for(int i=0; i<len; i++){
		numb^=data[i];
	}
	return numb;
}

void StartCommand(){
	uint8_t data[1] = {START_COMMAND};
	uint32_t timer = 0;
	while(action.flag != ACK){
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
	if(AwaitResponce(DATA, ANSWER_WAIT_TIME) == AN_ERROR){
		recive.command = RECIVE_STATE;
		recive.length = 1;
		return AN_ERROR;
	}
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


