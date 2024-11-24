#ifndef CRC_H
#define CRC_H

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

uint16_t crc16(uint16_t crc_now ,uint8_t *data, uint16_t size) {
	uint16_t crc = crc_now;

	for (uint16_t j = 0; j < size; j++)
	{
		crc ^= data[j] << 8;
		for (uint8_t i = 0; i < 8; i++)
			crc = crc & 0x8000 ? (crc << 1) ^ POLY : crc << 1;
	}
	return crc;
}

uint8_t crcAN3155(uint8_t *data, uint8_t len){
	uint8_t numb = 0;
	for(int i=0; i<len; i++){
		numb^=data[i];
	}
	return numb;
}



#endif // CRC16_H
