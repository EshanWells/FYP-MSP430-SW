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

volatile uint16_t errorCountGeneral = 0;
volatile uint16_t errorCountEE = 0;
volatile uint16_t errorCountI2C = 0;

volatile LOG_FSM logState = STARTUP;
volatile LOG_FSM nextLogState;

//! Implement Debug Channel, potentially through UART

int main(void)
{
  sysInit();

  timer0Counter0(6000, 1);

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

  EE_ReadbackRaw();

  while (1)
  {
    if (doTickRoutine())
    {
      static uint16_t count = 0;
      LED_TGLE;

      uint16_t sweeeeeet = SHT_getSerialNumber();
      SHT_RESULT_S reading;
      // reading.temp = 690;
      // reading.rHum = 42;
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

    //* Main State Machine

    //! I need to set up Timer B as my delay timer for this to work.
    //! Short term, Timer A can be the RTC 'Alarm' line which is fine realy.
    //? I need to figure out if I'm clearing LPM bits in the timer and setting manually in FSM
    //? or if I'll extensively use 'sleep' mode between modules?

    switch (logState)
    {
    case STARTUP:
      // non core boot code?
      // probably check for an EE reset condition?
      break;

    case MENU:
      // maybe present some options? Log, Readback, etc.
      break;

    case MCP_READ:
      // get current date time from MCP.
      // set next state
      // short term the tick count will suffice.
      break;

    case SHT_START:
      // send code to start a reading from SHT sensor
      // set next state
      // sleep for the time required.
      break;

    case SHT_READ:
      // get the data from SHT
      // process that data
      // set next state
      break;

    case EE_WRITE:
      // final format data for EE, including a struct
      // write data to EE
      // set next state
      // sleep for an appropriate time
      break;

    case EE_READ:
      // read back EE data from last address written
      // check it matches what we just sent
      // if it does, move onto next state
      // if not, we got an error

      // consider goiong back to write for a few turns.
      break;

    case MCP_WRITEALARM:
      // set alarm for RTC
      break;

    case SLEEP:
      // Set up sleep mode
      break;

    case LOG_READBACK_RAW:
    {
      EE_ReadbackRaw();
      break;
    }

      //! in these error sections, somehow display an error then transition to a known state
      //! Implement watchdog timer

    case GENERAL_ERROR:
      while (1); // implement error counter?
      break;

    case EE_ERROR:
      while (1);
      break;

    case I2C_ERROR:
      while (1)
        ;
      break;

    case RESET:
      // EE clearing code?
      break;

    default:
      while (1)
        ; // error counter then fire back to start
      break;
    }

    // LPM3;
  }
}
