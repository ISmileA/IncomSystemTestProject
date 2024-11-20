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

#define BOOT_PIN	GPIO_PIN_12
#define RESET_PIN	GPIO_PIN_11
#define BOOT_PORT	GPIOC
#define RESET_PORT	GPIOC

void BootModeStart(){
	HAL_GPIO_WritePin(BOOT_PORT, BOOT_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);
}


#endif /* INC_COMMANDMODULE_H_ */
