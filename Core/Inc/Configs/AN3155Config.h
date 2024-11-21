/*
 * AN3155Config.h
 *
 *  Created on: Nov 21, 2024
 *      Author: arsen
 */

#ifndef INC_CONFIGS_AN3155CONFIG_H_
#define INC_CONFIGS_AN3155CONFIG_H_

#define	ACK					0x79
#define NACK				0x1F

#define MAX_DATA			256U

#define START_COMMAND		0x7F
#define	READ_COMMAND		0x11
#define GO_COMMAND			0x21

#define RECIVE_STATE		0x01
#define RECIVE_DATA			0x02

#define ANSWER_WAIT_TIME	100 // mls


#endif /* INC_CONFIGS_AN3155CONFIG_H_ */
