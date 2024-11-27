/*
 * CommandModule.h
 *
 *  Created on: Nov 20, 2024
 *      Author: ISmileA
 */

#ifndef INC_COMMANDMODULE_H_
#define INC_COMMANDMODULE_H_

#include "main.h"
#include "Configs/BootConfig.h"
#include "Modules/Crc16Module.h"

#define BOOT_PIN	GPIO_PIN_15
#define RESET_PIN	GPIO_PIN_14
#define BOOT_PORT	GPIOC
#define RESET_PORT	GPIOC

#define AN_OK	0x01
#define AN_ERROR 0x00

void BootModeStart();
void BootModeEnd();

void StartCommand();

uint8_t ReadFlashData(uint32_t address, uint16_t len);
uint8_t GoInProgramm(uint32_t address);


#endif /* INC_COMMANDMODULE_H_ */
