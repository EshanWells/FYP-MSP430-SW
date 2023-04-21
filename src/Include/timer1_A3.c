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

void stateSwitchTimer(uint16_t delay)
{
    TA1CTL |= TACLR;
    TA1CCR0 = delay;
    TA1CTL = TASSEL_1 + ID_3;

    TA1CCTL0 = CCIE;
    TA1CTL |= MC_1;
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_CCR0_ISR(void)
{
    TA1CCTL0 &= ~CCIFG;

    setLOGState(getNextLOGState);
    __bic_SR_register_on_exit(LPM4_bits);
}
