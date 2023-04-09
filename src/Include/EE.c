/**
 * @file EE.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief Source file for 24LC512 EEPROM. May work with other 24 series. Requires I2C library.
 * @version 0.1
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "EE.h"

#define EE_I2C_ADDR 0x50

void EE_read(uint16_t memAddr, uint8_t *pData, uint8_t length)
{
    uint8_t address[] = {(memAddr >> 8) & 0xFF, memAddr & 0xFF};
    I2C_write(EE_I2C_ADDR, address, 2);
    I2C_read(EE_I2C_ADDR, pData, length);
}

