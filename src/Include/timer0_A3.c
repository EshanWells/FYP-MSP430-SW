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

/*****************************************/

#define MPU6050_ADDRESS 0x68

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_CCR0_ISR(void)
{
    TA0CCTL0 &= ~CCIFG;
    static volatile uint32_t count = 0;
    LED_TGLE;

    UCB0CTL1 |= UCTXSTT;

    char messageHolder[64] = {0};
    sprintf(messageHolder, "Tick: %d | %d %d %d %d %x %d \n", count, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6);
    uartPrintString(messageHolder, 64);
    count++;

}
