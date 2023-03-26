#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>
#include "core.h"

/**
 * @brief initialise I2C as a master, 100khz
 * 
 */
void initI2C (void);

/**
 * @brief enable module
 * 
 */
inline void I2CEnable (void);

/**
 * @brief disable module
 * 
 */
inline void I2CDisable (void);

//void I2CWrite (uint8_t slaveAddr, uint8_t* reg_addr, uint8_t reg_len, uint8_t* data, uint8_t len);

/**
 * @brief Barebones transmit
 * 
 * @param slaveAddr only supports 7 bit adressing mode
 * @param data pointer to data, array suggested
 * @param len length
 */
void I2CTransmit (uint8_t slaveAddr, uint8_t* data, uint8_t len);

/**
 * @brief 
 * 
 * @param slaveAddr 
 * @param data 
 * @param len 
 */
void I2CReceive (uint8_t slaveAddr, uint8_t* data, uint8_t len);

#endif
