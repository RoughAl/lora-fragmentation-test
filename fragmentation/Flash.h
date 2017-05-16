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
#ifndef __FLASH_MCU_H__
#define __FLASH_MCU_H__

#include "mbed.h"
#define DATA_EEPROM_BASE       ( ( uint32_t )0x8000000)              /*!< DATA_EEPROM base address in the alias region */
#define DATA_EEPROM_OFFSET       ( ( uint32_t )0x040000  )              /*!< DATA_EEPROM base address in the alias region */
#define DATA_EEPROM_END        ( ( uint32_t )DATA_EEPROM_BASE + 2048 *128) /*!< DATA EEPROM end address in the alias region */
void EepromMcuWriteBuffer( uint32_t addr, uint8_t *buffer, uint16_t size, int bank );
void EepromMcuReadBuffer( uint32_t addr, uint8_t *buffer, uint16_t size , int bank );
void StoreImageInFlash (uint8_t *buffer,uint32_t bufferSize );
void EraseFlash (void);
void EraseSector6 (void);
void StoreLineImageInFlash (uint32_t addr, uint8_t *buffer, uint32_t bufferSize );
void FlashPageErase( uint32_t page, uint32_t banks );
extern  uint8_t copyPage [2048] ; 
extern Serial pcf; 
#endif // __FLASH_MCU_H__




