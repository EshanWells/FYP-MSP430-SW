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

      RTC_REG_IF_S dateSet;
      dateSet.address = 0x00;
      dateSet.date.sec = 0x80;
      dateSet.date.min = 0x00;
      dateSet.date.hour = 0x00;
      dateSet.date.wkday = SUNDAY;
      dateSet.date.day = 0x01;
      dateSet.date.mth = 0x01;
      dateSet.date.year = 0x70;
      
      I2C_write(MCP7940_ADDR, (uint8_t *)&dateSet, 8);

  while (1)
  {
    if (doTickRoutine())
    {
      static uint16_t count = 0;
      LED_TGLE;

      uint16_t sweeeeeet = SHT_getSerialNumber();
      SHT_RESULT_S reading;
      //reading.temp = 690;
      //reading.rHum = 42;
      reading = SHT_getMedReading();

      RTC_REG_IF_S current;

      uint8_t txData[1] = {0x00};

      I2C_write(MCP7940_ADDR, txData, 1);
      I2C_read(MCP7940_ADDR, (uint8_t *)&current, 7);

      char messageHolder[64] = {0};
      sprintf(messageHolder, "Tick: %u | %d %d %d DateTime: %d:%d:%d \n", count, sweeeeeet, reading.temp, reading.rHum, current.date.hour, current.date.min, current.date.sec);
      uartPrintString(messageHolder, 64);
      count++;
    }
  }
}
