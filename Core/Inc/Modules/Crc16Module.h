/*
 * Crc16Module.h
 *
 *  Created on: Nov 26, 2024
 *      Author: arsen
 */

#ifndef INC_MODULES_CRC16MODULE_H_
#define INC_MODULES_CRC16MODULE_H_

#include "main.h"

/*
  Name  : CRC-16 CCITT
  Poly  : 0x1021    x^16 + x^12 + x^5 + 1
  Init  : 0xFFFF
  Revert: false
  XorOut: 0x0000
  Check : 0x29B1 ("123456789")
  MaxLen: 4095 байт (32767 бит) - обнаружение одинарных, двойных, тройных и всех нечетных ошибок
*/
#define POLY 0x1021

static uint16_t crc16(uint16_t crc_now ,uint8_t *data, uint16_t size) {
	uint16_t crc = crc_now;

	for (uint16_t j = 0; j < size; j++)
	{
		crc ^= data[j] << 8;
		for (uint8_t i = 0; i < 8; i++)
			crc = crc & 0x8000 ? (crc << 1) ^ POLY : crc << 1;
	}
	return crc;
}

//static uint16_t ModBusCRC16(uint16_t crc16_now, uint8_t *data, uint16_t len)
//{
//    uint16_t i, j, tmp, crc16 = crc16_now;
//
//    for (i = 0; i < len; i++)
//    {
//        crc16 ^= ((uint8_t)data[i]);
//        for (j = 0; j < 8; j++)
//        {
//            tmp = (uint16_t)(crc16 & 0x0001);
//            crc16 >>= 1;
//            if (tmp == 1)
//            {
//                crc16 ^= 0xa001; // тоже или полиномиальный
//            }
//        }
//    }
//    return crc16;
//}

#endif /* INC_MODULES_CRC16MODULE_H_ */
