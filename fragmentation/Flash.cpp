/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Timer objects and scheduling management

License: Revised BSD License, see LICENSE.TXT file include in the project

*/
#include "mbed.h"
#include "Flash.h"
#include "FragmentationDecode.h"

uint8_t copyPage [2048] ;
void FlashPageErase( uint32_t page, uint32_t banks )
{
    printf("FlashPageErase page=%d banks=%d\n", page, banks);
}

void EepromMcuWriteBuffer( uint32_t addr, uint8_t *buffer, uint16_t size, int bank )
{
    printf("EepromMcuWriteBuffer, addr=%d, size=%d, bank=%d\n", addr, size, bank);
}

void EepromMcuReadBuffer( uint32_t addr, uint8_t *buffer, uint16_t size , int bank )
{
    printf("EepromMcuReadBuffer, addr=%d, size=%d, bank=%d\n", addr, size, bank);
}

void StoreImageInFlash (uint8_t *buffer,uint32_t bufferSize )
{
    printf("StoreImageInFlash, size=%d\n", bufferSize);
}

void EraseSector6 (void)
{
    printf("EraseSector6\n");
}

void StoreLineImageInFlash (uint32_t addr, uint8_t *buffer, uint32_t bufferSize )
{
    printf("StoreLineImageInFlash addr=%d, size=%d\n", addr, bufferSize);
}
