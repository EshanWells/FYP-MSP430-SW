/*
https://www.artfulbytes.com/mcu-i2c-driver This was fairly instrumental in getting this working...
*/

#include "I2C.h"

#include <msp430.h>
#include "core.h"

/***Globals***/

uint8_t TXByteCtr;
uint8_t RXByteCtr;
uint8_t *pTxData;
uint8_t *pRxData;

/*************/

void initI2C(void)
{
    P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    
    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0I2CSA = 0x00;                         // Set slave address
    
    IE2 &= ~UCB0RXIE;  						  // Disable RX interrupt
	IE2 &= ~UCB0TXIE;  						  // Disable TX interrupt

    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
}

inline void I2CEnable (void)
{
    UCB0CTL1 &= ~UCSWRST;
}

inline void I2CDisable (void)
{
    UCB0CTL1 |= UCSWRST;
}

void I2CTxInit (uint8_t slaveAddr)
{
    IE2 &= ~UCB0RXIE;

    I2CDisable();
    UCB0I2CSA = slaveAddr;
    I2CEnable();

    IE2 |= UCB0TXIE;
}

void I2CRxInit (uint8_t slaveAddr)
{
    IE2 &= ~UCB0TXIE;

    I2CDisable();
    UCB0I2CSA = slaveAddr;
    I2CEnable();

    IE2 |= UCB0RXIE;
}

void I2C TxMultiByte(uint8_t slaveAddr, )
