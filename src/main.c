/**
 * @file main.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief For MSP430G2553
 *        main.c for FYP at DMU. Low power shipping container environment logger.
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <msp430.h>

#include "core.h"

/**
 * main.c
 */

#define EE_ADDR 0x50


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
      static uint16_t count = 0;
      LED_TGLE;

      //uint16_t sweeeeeet = SHT_getSerialNumber();
      SHT_RESULT_S reading;
      //reading = SHT_getMedReading();

      char messageHolder[64] = {0};
      sprintf(messageHolder, "Tick: %u | %d %d %d %x %d %d \n", count, 1, 2, 3, 4, reading.temp, reading.rHum);
      uartPrintString(messageHolder, 64);
      count++;
    }
  }
}
