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
#include "gpio.h"

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

      uint8_t pageMarker[] = "FW";
      //EE_write(0x0000, pageMarker, 2);

      uint8_t rxData[3] = {0};
      uint8_t txData[] = {0x11, 0x22};

      EE_read(0x00, rxData, 2);

      char messageHolder[64] = {0};
      sprintf(messageHolder, "Tick: %d | %d %d %d %c %c %d \n", count, 1, 2, 3, rxData[0], rxData[1], rxData[2]);
      uartPrintString(messageHolder, 64);
      count++;
    }
  }
}
