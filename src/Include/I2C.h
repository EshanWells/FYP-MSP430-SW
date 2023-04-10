/**
 * @file I2C.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief I2C header for USCIB module
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef I2C_H_
#define I2C_H_
#include "core.h"

/**
 * @brief init function nothing fancy, ~100khz given dco ~1.2mhz
 *
 */
void I2C_init(void);

/**
 * @brief Hold module in reset
 *
 */
inline void I2C_enable(void);

/**
 * @brief take module out of reset
 *
 */
inline void I2C_disable(void);

/**
 * @brief send start condition
 *
 */
inline void I2C_setStart(void);

/**
 * @brief check if start condition is sent
 *
 * @return uint8_t low when sent, high when sending
 */
inline uint8_t I2C_isStart(void);

/**
 * @brief send stop condition
 *
 */
inline void I2C_setStop(void);

/**
 * @brief check if stop condition is sent
 *
 * @return uint8_t low when sent, high when sending
 */
inline uint8_t I2C_isStop(void);

/**
 * @brief set nonacknowledge bit. Don't think i use this.
 *
 */
inline void I2C_setNack(void);

/**
 * @brief return 1 if TX buffer empty.
 *
 * @return uint8_t
 */
inline uint8_t I2C_isTxBufEmpty(void);

/**
 * @brief return 1 if receive buffer full
 *
 * @return uint8_t
 */
inline uint8_t I2C_isRxBufFull(void);

/**
 * @brief check if bus occupied
 *
 * @return uint8_t
 */
inline uint8_t I2C_isBusBusy(void);

/**
 * @brief did we receive a NACK?
 *
 * @return uint8_t
 */
inline uint8_t I2C_rxedNack(void);

/**
 * @brief initialise write with slaveaddress
 *
 * @param slaveAddr right justified without RW bit
 */
void I2C_txInit(uint8_t slaveAddr);

/**
 * @brief intilialise receive with slave address
 *
 * @param slaveAddr right justified without RW bit
 */
void I2C_rxInit(uint8_t slaveAddr);


/**
 * @brief set slave address incl module reset
 *
 * @param slaveAddr right justified without RW bit
 */
void I2C_setSlaveAddr(uint8_t slaveAddr);

/**
 * @brief transmit byte, with delays to let it send
 *
 */
void I2C_transmit(uint8_t txByte);

/**
 * @brief receive byte, polling to check for read
 *
 * @return uint8_t byte rxed
 */
uint8_t I2C_receive(void);

/**
 * @brief perform a write on EE
 *
 * @param slaveAddr right justified without RW
 * @param txData pointer to data array
 * @param dataLength how long is that array
 */
void I2C_write(uint8_t slaveAddr, uint8_t *txData, uint8_t dataLength);

/**
 * @brief
 *
 * @param slaveAddr
 * @param rxData
 * @param dataLength
 */
void I2C_read(uint8_t slaveAddr, uint8_t *rxData, uint8_t dataLength);

#endif //I2C_H
