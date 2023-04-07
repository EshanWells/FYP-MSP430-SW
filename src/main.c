#include <msp430.h>

#include "core.h"
#include "gpio.h"

/**
 * main.c
 */
int main(void)
{
  sysInit();

  timer0Counter0(16384, 1);

  __bis_SR_register(GIE);

  // Is the head still detatched???

  while (1)
  {
    if (doTickRoutine())
    {
      static volatile uint16_t count = 0;
      LED_TGLE;

      char messageHolder[64] = {0};
      sprintf(messageHolder, "Tick: %d | %d %d %d %d %x %d \n", count, 1, 2, 3, 4, 5, 6);
      uartPrintString(messageHolder, 64);
      count++;

      I2C_setStart();
    }
  }
}
