/**
 * @file timer0_A3.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief barebones Timer driver with one CC interrupt configured.
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "timer0_A3.h"

#include "core.h"

#define ALARM_INTERVAL 15 //seconds

void timer0Counter0(uint16_t delay)
{
    // set up Timer0_A3
    TA0CCR0 = delay;      // set compare register to desired delay
    TA0CTL = TASSEL_1 + ID_0; // use ACLK as source, div 8

    // clear any pending interrupts and enable global interrupts
    TA0CCTL0 = CCIE;          // enable timer interrupt
    TA0CTL |= TACLR;         // clear timer

    // start timer
    TA0CTL |= MC_1;          // enable timer
}

void startTimer(void)
{
    TA0CTL |= MC_1;
}

void stopTimer0(void)
{
    TA0CTL &= ~MC_1;
}

/*****************************************/

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_CCR0_ISR(void) //this may not work
{
    incrementTicks();
    LED_TGLE;

    if(getCoreMode() == LOGGING) //check if we're in logging mode
    {
        if((ticks() % ALARM_INTERVAL) == 0) //is it time for an alarm?
        {
            setLogState(MCP_READ);
            __bic_SR_register_on_exit(LPM3_bits);
        }
    }
}
