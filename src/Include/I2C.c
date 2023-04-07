/*
I've written this one almost completely myself. It's really messy. And it's taken a good couple of weeks to get happy.

The logic analyzer was instrumental in getting this going, as none of the examples worked as expected.
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

    UCB0CTL1 |= UCSWRST;                  // Enable SW reset
    
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

void I2C_txInit(void)
{
   I2C_disable();
   UCB0CTL1 |= UCTR;
   I2C_enable(); 
}

void I2C_rxInit(void)
{
    I2C_disable();
    UCB0CTL1 &= ~UCTR;
    I2C_enable();
}

void I2C_setSlaveAddr(uint8_t slaveAddr)
{
    I2C_disable();
    UCB0I2CSA = slaveAddr;
    I2C_enable();
}

void I2C_transmit(uint8_t txByte)
{
    while(!I2C_isTxBufEmpty); //wait for buff to be empty
    UCB0TXBUF = txByte;   
}
