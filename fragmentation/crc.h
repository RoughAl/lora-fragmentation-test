/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2017 Semtech

Description: 	Firmware update over the air with LoRa proof of concept
				Functions for the decoding
*/
#include "mbed.h"
#ifndef _CRC_H
#define _CRC_H
void Crc64(uint8_t *dataIn, int size,uint32_t * crcLow, uint32_t * crcHigh );

#endif /* _crc_h */


