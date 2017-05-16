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
#include "crc.h"
#include "mbed.h"
#include "Flash.h"
#define POLY64REV     0x95AC9329AC4BC9B5
#define INITIALCRC    0xFFFFFFFFFFFFFFFF

void Crc64(uint8_t *dataIn, int size,uint32_t * crcLow, uint32_t * crcHigh )
{
    int i, j;
    uint64_t crc = INITIALCRC, part;
    static int init = 0;
    static  uint64_t  CRCTable[256];

    if (!init) {
        init = 1;
        for (i = 0; i < 256; i++) {
            part = i;
            for (j = 0; j < 8; j++) {
                if (part & 1)
                    part = (part >> 1) ^ POLY64REV;
                else
                    part >>= 1;
            }
            CRCTable[i] = part;
        }
    }

    for (i = 0 ; i < size ; i++) {

        crc = CRCTable[(crc ^ *dataIn++) & 0xff] ^ (crc >> 8);
    }
    /*
     The output is done in two parts to avoid problems with
     architecture-dependent word order
     */
    *crcLow = crc & 0xffffffff;
    *crcHigh = (crc >> 32) & 0xffffffff ;

}

