#ifndef I2C_H_
#define I2C_H_
#include "core.h"

void I2C_init(void);
inline void I2C_enable(void);
inline void I2C_disable(void);
inline void I2C_setStart(void);
inline uint8_t I2C_isStart(void);
inline void I2C_setStop(void);
inline uint8_t I2C_isStop(void);
inline void I2C_setNack(void);
inline uint8_t I2C_isTxBufEmpty(void);
inline uint8_t I2C_isRxBufFull(void);
inline uint8_t I2C_isBusBusy(void);
inline uint8_t I2C_rxedNack(void);
void I2C_txInit(uint8_t slaveAddr);
void I2C_rxInit(uint8_t slaveAddr);
void I2C_setSlaveAddr(uint8_t);
void I2C_transmit(uint8_t);
uint8_t I2C_receive(void);
void I2C_write(uint8_t slaveAddr, uint8_t *txData, uint8_t dataLength);
void I2C_read(uint8_t slaveAddr, uint8_t *rxData, uint8_t dataLength);

#endif //I2C_H
