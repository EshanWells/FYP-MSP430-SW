#include "gpio.h"
#include "core.h"

void initGPIO(void)
{
    P1DIR |= BIT0 + BIT3 + BIT4 + BIT5;
    P1REN |= BIT3 + BIT4 + BIT5;
    P1OUT = 0x00;

    P2DIR |= BIT2 + BIT3 + BIT4;
    P2DIR &= ~BIT0 + ~BIT1 + ~BIT5;
    P2REN = 0x00;

    P3DIR = 0xFF;
    P3REN = 0xFF;
    P3OUT = 0x00;
}
