/*
https://www.artfulbytes.com/mcu-i2c-driver This was fairly instrumental in getting this working...
*/

#include "I2C.h"

#include <msp430.h>
#include "core.h"

void initI2C(void)
{
    P1DIR &= ~(BIT6 + BIT7);  // Set pins to input
    P1REN &= ~(BIT6 + BIT7);  // Disable pull-up/down resistors
    P1OUT &= ~(BIT6 + BIT7);  // Set output value to low
    
    P1SEL |= BIT6 + BIT7;  // Select I2C pins
    P1SEL2 |= BIT6 + BIT7;

    UCB0CTL1 |= UCSWRST; //device in reset before configuring
    UCB0CTL0 = UCMST + UCSYNC + UCMODE_3; // 1 master, sync, I2C
    UCB0CTL1 |= UCSSEL_2; //clock off SMCLK
    UCB0BR0 = 10; //prescaler div by 10, so 100khz transmission
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST; //clear reset bit
}

inline void I2CEnable(void)
{
    UCB0CTL1 &= ~UCSWRST;
}

inline void I2CDisable(void)
{
    UCB0CTL1 |= UCSWRST;
}


