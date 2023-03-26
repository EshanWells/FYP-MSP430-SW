#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>
#include "core.h"

/**
 * @brief initialise I2C as a master, 100khz
 * 
 */
void initI2C(void);

inline void I2CEnable(void);

inline void I2CDisable(void);

#endif
