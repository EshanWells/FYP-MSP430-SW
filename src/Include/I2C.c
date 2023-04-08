/*
I've written this one almost completely myself. It's really messy. And it's taken a good couple of weeks to get happy.

The logic analyzer was instrumental in getting this going, as none of the examples worked as expected.

As of 08/04/2023, this is working as I'd hope.
*/

#include "I2C.h"

#include <msp430.h>
#include "core.h"

/***Globals***/

uint8_t byteCtr;
uint8_t *pTxData;
uint8_t *pRxData;

/*************/

void I2C_init(void)
{
    P1SEL |= BIT6 + BIT7;  // Assign I2C pins to USCI_B0
    P1SEL2 |= BIT6 + BIT7; // Assign I2C pins to USCI_B0

    UCB0CTL1 |= UCSWRST; // Enable SW reset

    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;        // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                         // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0I2CSA = 0x00; // Set slave address

    IE2 &= ~UCB0RXIE; // Disable RX interrupt
    IE2 &= ~UCB0TXIE; // Disable TX interrupt

    UCB0CTL1 &= ~UCSWRST; // Clear SW reset, resume operation
}

inline void I2C_enable(void)
{
    UCB0CTL1 &= ~UCSWRST;
}

inline void I2C_disable(void)
{
    UCB0CTL1 |= UCSWRST;
}

inline void I2C_setStart(void)
{
    UCB0CTL1 |= UCTXSTT;
}

inline uint8_t I2C_isStart(void)
{
    return (UCB0CTL1 & UCTXSTT);
}

inline void I2C_setStop(void)
{
    UCB0CTL1 |= UCTXSTP;
}

inline uint8_t I2C_isStop(void)
{
    return (UCB0CTL1 & UCTXSTP);
}

inline void I2C_setNack(void)
{
    UCB0CTL1 |= UCTXNACK;
}

inline uint8_t I2C_isTxBufEmpty(void)
{
    return (IFG2 & UCB0TXIFG);
}

inline uint8_t I2C_isRxBufFull(void)
{
    return (IFG2 & UCB0RXIFG);
}

inline uint8_t I2C_isBusBusy(void)
{
    return (UCB0STAT & UCBBUSY);
}

inline uint8_t I2C_rxedNack(void)
{
    return (UCB0CTL1 & UCNACKIFG);
}

void I2C_txInit(uint8_t slaveAddr)
{
    I2C_disable();
    UCB0CTL1 |= UCTR;
    UCB0I2CSA = slaveAddr;
    I2C_enable();
}

void I2C_rxInit(uint8_t slaveAddr)
{
    I2C_disable();
    UCB0CTL1 &= ~UCTR;
    UCB0I2CSA = slaveAddr;
    I2C_enable();
}

void I2C_setSlaveAddr(uint8_t slaveAddr)
{
    UCB0I2CSA = slaveAddr;
}

void I2C_transmit(uint8_t txByte)
{
    while (!I2C_isTxBufEmpty());
    UCB0TXBUF = txByte;
    while (!I2C_isTxBufEmpty());
}

uint8_t I2C_receive(void)
{
    while (!I2C_isRxBufFull());
    uint8_t rxData = UCB0RXBUF;
    return rxData;
}

void I2C_write(uint8_t slaveAddr, uint8_t *txData, uint8_t dataLength)
{
    I2C_txInit(slaveAddr);
    I2C_setStart();
    uint8_t index;
    for(index = 0; index < dataLength; index++)
    {
        I2C_transmit(txData[index]);
    }
    I2C_setStop();
    while(I2C_isStop());
}

void I2C_read(uint8_t slaveAddr, uint8_t *rxData, uint8_t dataLength)
{
    I2C_rxInit(slaveAddr);
    I2C_setStart();
    uint8_t index;
    for(index = 0; index < dataLength; index++)
    {
        rxData[index] = I2C_receive();
    }
    I2C_setStop();
    while(I2C_isStop());
}
