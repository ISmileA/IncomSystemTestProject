/*
 * ActionModule.h
 *
 *  Created on: Nov 26, 2024
 *      Author: ISmileA
 */

#ifndef INC_MODULES_ACTIONMODULE_H_
#define INC_MODULES_ACTIONMODULE_H_

#include "main.h"
#include "CommandModule.h"


uint32_t byteReads = 0;
uint32_t dataSize = 0;
uint16_t crc16_schet = 0;
uint16_t read = MAX_DATA;

volatile uint16_t crc_now = 0xFFFF;

void GetDataSize(uint32_t address){
	if(ReadFlashData(address, 4)){
		dataSize = (uint32_t)(action.data[3] << 24) |
		(uint32_t)(action.data[2] << 16) | (uint32_t)(action.data[1] << 8) |
		(uint32_t)(action.data[0]);
		action.command = GET_CRC16;
	}
}

void GetCrc16(uint32_t address){
	if(ReadFlashData(address, 2)){
		crc16_schet = (uint16_t)(action.data[1] << 8) |
		(uint16_t)(action.data[0]);
		action.command = READ_DATA;
	}
}

void ReadMemoryOnDevice(uint32_t address){
	if(ReadFlashData(address+byteReads, read) && dataSize >= read){
		byteReads+=read;
		crc_now = crc16(crc_now, action.data, read);
		if((dataSize-byteReads) == 0){
		  action.command = GO_COMMAND;
		}else if((dataSize-byteReads) < read){
		  read = (dataSize-byteReads);
		}
	}
}

void VerifyAndGo(uint32_t address){
	if(crc16_schet == crc_now){
		if(GoInProgramm(address)){
			BootModeEnd();
			action.command = SUCCESS_LOG;
		}
	}else
		action.command = ERROR_LOG;
}

#endif /* INC_MODULES_ACTIONMODULE_H_ */
