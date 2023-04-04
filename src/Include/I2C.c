/*
https://www.artfulbytes.com/mcu-i2c-driver This was fairly instrumental in getting this working...
*/

#include "I2C.h"

#include <msp430.h>
#include "core.h"

/***Globals***/

uint8_t byteCtr;
uint8_t *pTxData;
uint8_t *pRxData;

/*************/

void initI2C(void)
{
    P1SEL |= BIT6 + BIT7;  // Assign I2C pins to USCI_B0
    P1SEL2 |= BIT6 + BIT7; // Assign I2C pins to USCI_B0

    UCB0CTL1 |= UCSWRST;                  // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;        // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                         // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    //UCB0I2CSA = 0x00; // Set slave address

    IE2 &= ~UCB0RXIE; // Disable RX interrupt
    IE2 &= ~UCB0TXIE; // Disable TX interrupt

    UCB0CTL1 &= ~UCSWRST; // Clear SW reset, resume operation
}

inline void I2CEnable(void)
{
    UCB0CTL1 &= ~UCSWRST;
}

inline void I2CDisable(void)
{
    UCB0CTL1 |= UCSWRST;
}

void I2CTxInit(uint8_t slaveAddr, uint8_t prescale)
{
    IE2 &= ~UCB0RXIE;

    I2CDisable();
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;        // Use SMCLK, keep SW reset
    UCB0I2CSA = slaveAddr;
    I2CEnable();

    IE2 |= UCB0TXIE;
}

void I2CRxInit(uint8_t slaveAddr, uint8_t prescale)
{
    IE2 &= ~UCB0TXIE;

    I2CDisable();
    UCB0I2CSA = slaveAddr;
    I2CEnable();

    IE2 |= UCB0RXIE;
}

// void I2C TxMultiByte(uint8_t slaveAddr, )

/*Test Function*/
unsigned char i2c_read_byte(unsigned char address, unsigned char reg)
{
    unsigned char data = 0;
    
    // send start condition
    UCB0CTL1 |= UCTR + UCTXSTT; // transmit mode, start condition
    while (UCB0CTL1 & UCTXSTT); // wait for start condition to be sent
    
    // send device address and register address
    UCB0TXBUF = address << 1; // send device address in write mode
    while (!(IFG2 & UCB0TXIFG)); // wait for TX buffer to be empty
    UCB0TXBUF = reg; // send register address
    while (!(IFG2 & UCB0TXIFG)); // wait for TX buffer to be empty
    
    // send repeated start condition
    UCB0CTL1 &= ~UCTR; // receive mode
    UCB0CTL1 |= UCTXSTT; // repeated start condition
    while (UCB0CTL1 & UCTXSTT); // wait for repeated start condition to be sent
    
    // send device address and read data
    UCB0TXBUF = address << 1 | 1; // send device address in read mode
    while (!(IFG2 & UCB0RXIFG)); // wait for RX buffer to receive device address
    UCB0CTL1 |= UCTXNACK; // send NACK to stop data transfer after reading one byte
    data = UCB0RXBUF; // read data
    
    // send stop condition
    UCB0CTL1 |= UCTXSTP; // stop condition
    
    return data;
}
