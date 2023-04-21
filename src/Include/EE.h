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

#define EE_I2C_ADDR 0x50

/**
 * @brief Read from EEPROM.
 *
 * @param memAddr 16 bit address, Big endian
 * @param pData pointer to ARRAY
 * @param length yeah
 */
void EE_read(uint16_t memAddr, uint8_t *pData, uint8_t length);

/**
 * @brief Write to EEPROM
 *
 * @param memAddr 16 bit address, big endian
 * @param pData must be array
 * @param length x
 */
void EE_write(uint16_t memAddr, uint8_t *pData, uint8_t length);

void EE_ReadbackRaw(void);

#endif
