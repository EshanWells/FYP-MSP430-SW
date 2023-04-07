#include <msp430.h> 

#include "core.h"
#include "gpio.h"

/**
 * main.c
 */
int main(void)
{
	sysInit();

	timer0Counter0(16384,1);

	__bis_SR_register(GIE);

  //need to rescue this.

	while(1)
	{
    if(doTickRoutine())
    {
    static volatile uint64_t count = 0;
    LED_TGLE;

    char messageHolder[128] = {0};
    sprintf(messageHolder, "Tick: %d | %d %d %d %d %x %d \n", count, 1, 2, 3, 4, who_am_i, 6);
    uartPrintString(messageHolder, 128);
    count++;
    }
	}
}
