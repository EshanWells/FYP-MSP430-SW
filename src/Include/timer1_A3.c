/**
 * @file timer1_A3.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "timer1_A3.h"
#include "core.h"

void stopTimer1(void)
{
    TA1CTL &= ~MC_1;
}

void timer1Counter0(uint16_t delay)
{
 // Stop timer
    TA1CTL = MC_0;

    // Set timer to count up using ACLK as source
    TA1CTL |= TASSEL_1 | ID_0;

    // Set timer period to 5000 (0.5s with ACLK = 32768Hz and divider on 8)
    TA1CCR0 = delay;

    // Enable timer interrupt
    TA1CCTL0 |= CCIE;

    // Start timer
    TA1CTL |= MC_1;

    // Enable interrupts globally
    __enable_interrupt();
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_CCR0_ISR(void) //this may not work
{
    TA1CCTL0 &= ~CCIFG;
    stopTimer1();
    setLogState(getNextLogState());
    __bic_SR_register_on_exit(LPM3_bits);
}

