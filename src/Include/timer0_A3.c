#include "timer0_A3.h"

#include "core.h"

void timer0Counter0(uint16_t delay, uint8_t code)
{
    setTimer0Code0(code); //experiment to see if we can pass some data through this.
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

void stopTimer(void)
{
    TA0CTL &= ~MC_1;
}

static volatile uint8_t timerCode = 0;

uint8_t getTimer0Code0(void)
{
    return timerCode;
}

void setTimer0Code0(uint8_t set)
{
    timerCode = set;
}

uint8_t T0A3IFG1 = 0;

uint8_t doTickRoutine(void)
{
    uint8_t rc = T0A3IFG1;
    T0A3IFG1 = 0;
    return rc;
}

/*****************************************/

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_CCR0_ISR(void)
{
    TA0CCTL0 &= ~CCIFG;
    T0A3IFG1 = 1;
}
