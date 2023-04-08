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


  I2C_setSlaveAddr(0b01010000);

  char startMessage[] = "\nContainer Logger Software Init Complete\n";
  uartPrintString(startMessage, strlen(startMessage));

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

      uint8_t rxData[3] = {0};

      I2C_txInit();
      I2C_setStart();
      I2C_transmit(0x11);
      I2C_transmit(0x22);
      I2C_setStop();
      
      I2C_rxInit();
      I2C_setStart();
      rxData[0] =  I2C_receive();
      rxData[1] =  I2C_receive();
      rxData[2] =  I2C_receive();
      I2C_setStop();
    }
  }
}
