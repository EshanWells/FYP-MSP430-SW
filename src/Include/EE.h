/**
 * @file EE.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief Header file for 24LC512 EEPROM. May work with other 24 series. Requires I2C library.
 * @version 0.1
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef EE_H_
#define EE_H_
#include "core.h"

void EE_read(uint16_t memAddr, uint8_t *pData, uint8_t length);

void EE_write(uint16_t memAddr, uint8_t *pData, uint8_t length);

#endif
