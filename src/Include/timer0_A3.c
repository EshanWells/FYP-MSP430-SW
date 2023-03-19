#include "timer0_A3.h"

#include "core.h"

void initTimer0(void)
{

}

void initT0CLK(void)
{
    //TA0CTL
}

void timer0Counter0(uint16_t delay)
{
    // set up Timer0_A3
    TA0CCR0 = delay;      // set compare register to desired delay
    TA0CTL = TASSEL_2 + ID_3; // use SMCLK as source, div 8

    // clear any pending interrupts and enable global interrupts
    __disable_interrupt();
    TA0CCTL0 = CCIE;          // enable timer interrupt
    TA0CTL |= TACLR + TAIE;         // clear timer
    __enable_interrupt();

    // start timer
    TA0CTL |= MC_1;          // enable timer
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_CCR0_ISR(void)
{
    TA0CTL &= ~MC_1;
    TA0CCTL0 &= ~CCIFG;
    blinkLED();
}

void blinkLED(void)
{
    P1OUT ^= 0x01;
    timer0Counter0(65535);
}
