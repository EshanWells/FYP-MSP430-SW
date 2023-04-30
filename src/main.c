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
  __bis_SR_register(GIE);

/*
  RTC_REG_IF_S dateSet;
  dateSet.address = 0x00;
  dateSet.date.sec = 0x80;
  dateSet.date.min = 0x00;
  dateSet.date.hour = 0x00;
  dateSet.date.wkday = SUNDAY;
  dateSet.date.day = 0x01;
  dateSet.date.mth = 0x01;
  dateSet.date.year = 0x70;

  I2C_write(MCP7940_ADDR, (uint8_t *)&dateSet, 8);*/

  while (1)
  {
    //* Main State Machine
    static unsigned long tickCount = 0;
    static SHT_RESULT_S tempHumReading;

    switch (logState)
    {
    case STARTUP:
      // non core boot code?
      // probably check for an EE reset condition?
      {
        char startMessage[] = "\r\nContainer Logger Software Init Complete\r\n";
        uartPrintString(startMessage, strlen(startMessage));

        setLogState(SLEEP);
        setNextLogState(MENU);
        timer1Counter0(4000);

        //*Do something like finding the start of the SLL!!!

      }
      break;

    case MENU:
      // maybe present some options? Log, Readback, etc.
      stopTimer1();
      {
        char messageHolder[40] = "\r\nContainer Logger Main Menu\r\n";
        uartPrintString(messageHolder, 40);
        strncpy(messageHolder, "   Num    Option\r\n  ----- ----------\r\n", 64);
        uartPrintString(messageHolder, 40);
        strncpy(messageHolder, "    1    Logging\r\n", 64);
        uartPrintString(messageHolder, 40);
        strncpy(messageHolder, "    2    Readback\r\n", 64);
        uartPrintString(messageHolder, 40);
        strncpy(messageHolder, "    3    EE Nuke\r\n", 64);
        uartPrintString(messageHolder, 40);
        //strncpy(messageHolder, "    4    Enter Time\r\n\r\n", 64);
        //uartPrintString(messageHolder, 40);
      }
      setLogState(SLEEP);
      setNextLogState(MENU);
      break;

    case MCP_READ:
      // get current date time from MCP.
      // set next state
      // short term the tick count will suffice.

      break;

//*START TEMP & HUM MEASUREMENT
    case SHT_START:
      // send code to start a reading from SHT sensor
      // set next state
      // sleep for the time required.
      {
        SHT_sendCommand(TRH_MID);
      }
      setLogState(SLEEP);
      setNextLogState(SHT_READ);
      timer1Counter0(100);//actual delay is 60 vlo cycles, this is error margin.
      break;

//*READ TEMP & HUM DATA
    case SHT_READ:
      // get the data from SHT
      // process that data
      // set next state
      {
        uint8_t rxData[6];
        I2C_read(SHT40_ADDR, rxData, 6);
        uint16_t tempMeas = (rxData[0] << 8) | rxData[1];
        long tempResult = (long)tempMeas * (175 * T_MULT);
        tempResult /= 65535;
        tempResult -= (45 * T_MULT);

        uint16_t humMeas = (rxData[3] << 8) | rxData[4];
        long humResult = (long)humMeas * (125 * H_MULT);
        humResult /= 65535;
        humResult -= (6*H_MULT);
        if(humResult < 0)
        {
            humResult = 0;
        }
        if(humResult > (100*H_MULT))
        {
            humResult = (100*H_MULT);
        }

        tempHumReading.temp = (int16_t)tempResult;
        tempHumReading.rHum = (uint8_t)humResult;

        char messageHolder[32] = {0};
        sprintf(messageHolder, "Temp: %d | RH: %d\r\n", tempHumReading.temp, tempHumReading.rHum);
        uartPrintString(messageHolder, 32);
      }
      setLogState(SLEEP);
      setNextLogState(SHT_START);
      timer1Counter0(65535);
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
      LPM3;
      break;

    case LOG_READBACK_RAW:
      {
        char message[24] = "\r\nReadback Start\r\n";
        uartPrintString(message, 24);
        EE_ReadbackRaw();
      }
      setLogState(MENU);
      break;

      //! in these error sections, somehow display an error then transition to a known state
      //! Implement watchdog timer

    case GENERAL_ERROR:
      break;

    case EE_ERROR:
      break;

    case I2C_ERROR:
      break;

    case EE_RESET:
      {
        char message[24] = "\r\nEE Wipe Started\r\n";
        uartPrintString(message, 24);
        uint8_t data[32]; //!Need to test the heck outta this bad boy
        uint8_t i;
        for(i = 0; i < 32; i++)
        {
          data[i] = 0x69;
        }
        uint16_t index = 0;
        for(index = 0; index < 2048; index++)
        {
          uint16_t address = index<<5;
          EE_write(address, data, 32);
          __delay_cycles(5500);
        }
        strncpy(message, "\r\nEE Wiped\r\n", 24);
        uartPrintString(message, 24);
        setLogState(MENU);
      }
      break;

    default:
      break;
    }
  }
}
