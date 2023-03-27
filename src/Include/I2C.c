/*
https://www.artfulbytes.com/mcu-i2c-driver This was fairly instrumental in getting this working...
*/

#include "I2C.h"

#include <msp430.h>
#include "core.h"

void initI2C(void)
{
    P1DIR &= ~(BIT6 + BIT7); // Set pins to input
    P1REN &= ~(BIT6 + BIT7); // Disable pull-up/down resistors
    P1OUT &= ~(BIT6 + BIT7); // Set output value to low

    P1SEL |= BIT6 + BIT7; // Select I2C pins
    P1SEL2 |= BIT6 + BIT7;

    UCB0CTL1 |= UCSWRST;                  // device in reset before configuring
    UCB0CTL0 = UCMST + UCSYNC + UCMODE_3; // 1 master, sync, I2C
    UCB0CTL1 |= UCSSEL_2;                 // clock off SMCLK
    UCB0BR0 = 10;                         // prescaler div by 10, so 100khz transmission
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST; // clear reset bit
}

inline void I2CEnable (void)
{
    UCB0CTL1 &= ~UCSWRST;
}

inline void I2CDisable (void)
{
    UCB0CTL1 |= UCSWRST;
}

/* I'm not convinced this is the right approach for this, as it may abstract too much at once. Let's try something else.
void I2CWrite (uint8_t slaveAddr, uint8_t* reg_addr, uint8_t reg_len, uint8_t* data, uint8_t len)
{
    UCB0I2CSA = slaveAddr;
    UCB0CTL1
}*/

void I2CTransmit (uint8_t slaveAddr, uint8_t* data, uint8_t len)
{
    UCB0I2CSA = slaveAddr;
    UCB0CTL1 |= UCTR + UCTXSTT;

    while (UCB0CTL1 & UCTXSTT); // wait for free buffer
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        UCB0TXBUF = data[i];
        while (!(IFG2 & UCB0TXIFG));
    }

    UCB0CTL1 |= UCTXSTP; // stop condition
}

void I2CReceive(uint8_t slaveAddr, uint8_t *data, uint8_t len)
{
    UCB0I2CSA = slaveAddr;
    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;

    while (UCB0CTL1 & UCTXSTT); //waits for start condition to be sent.

    uint8_t i;
    for (i = 0; i < len; i++)
    {
        if (i == len - 1)
        {
            UCB0CTL1 |= UCTXNACK; //indicate end of stream
            UCB0CTL1 |= UCTXSTP;
        }

        data[i] = UCB0RXBUF;
        while(!(IFG2 & UCB0RXIFG));
    }
}
