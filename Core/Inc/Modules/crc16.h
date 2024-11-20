#ifndef CRC16_H
#define CRC16_H

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

static uint16_t calc(uint8_t data[], uint16_t size) {
	uint16_t crc = 0xFFFF;

	for (uint16_t j = 0; j < size; j++)
	{
		crc ^= data[j] << 8;
		for (uint8_t i = 0; i < 8; i++)
			crc = crc & 0x8000 ? (crc << 1) ^ POLY : crc << 1;
	}
	return crc;
}

#endif // CRC16_H
