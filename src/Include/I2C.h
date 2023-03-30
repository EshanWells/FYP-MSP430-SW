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

void I2CTxInit (uint8_t slaveAddr);

void I2CRxInit (uint8_t slaveAddr);

#endif
