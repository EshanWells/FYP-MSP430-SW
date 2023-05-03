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

uint16_t errorCountGeneral = 0;
uint16_t errorCountEE = 0;
uint16_t errorCountI2C = 0;

volatile LOG_FSM logState = STARTUP;
volatile LOG_FSM nextLogState;

volatile CORE_MODE coreMode = IDLE;

//*Log Indexes
uint16_t currentLogIndex = 0;
uint16_t lastLogIndex = 0;

volatile unsigned long long tickCount = 0;

int main(void)
{
  sysInit();
  __bis_SR_register(GIE);

  timer0Counter0(12000); //start main tick counter

  while (1)
  {
    static PAYLOAD_S payload;

    //* Main State Machine

    switch (logState)
    {




//*Logger Startup Routine
    case STARTUP:
      // non core boot code?
      // probably check for an EE reset condition?
      {
        //*Do something like finding the start of the SLL!!!
        uint8_t result[1] = {0x00};
        uint16_t peAddrEE = 0x0000; //external pointer to ee address for this process.

        EE_read(peAddrEE, (uint8_t *)result, 1); //read 1st location
        
        if(result[0] == 0x5A) //first location is written fine.
        {
          peAddrEE += 0x0010; //incrememnt ee pointer
          uint8_t headFound = 0;

          while(!headFound) //increment through the loop until we find the first unwritten location
          {
            EE_read(peAddrEE, (uint8_t *)result, 1);

            if(result[0] == 0x5A)
            {
              peAddrEE += 0x0010;
            } else {
              headFound = 1;
            }
          }
          currentLogIndex = peAddrEE >>4; //current 'head'
          lastLogIndex = currentLogIndex - 1; //last written location
        } else { //this situation arises on a clean EEPROM.
          currentLogIndex = 0;
          lastLogIndex = 0;
        }

        char startMessage[] = "\r\nContainer Logger Software Init Complete\r\n";
        uartPrintString(startMessage, strlen(startMessage));

        setLogState(MENU);
        setNextLogState(MENU);

      }
      break;




//*Present Menu
    case MENU:
      stopTimer1();
      setCoreMode(IDLE);
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

        sprintf(messageHolder, "\r\n\nCurrently %d Log Entries\r\n", currentLogIndex);
        uartPrintString(messageHolder, 40);
      }
      setLogState(SLEEP);
      setNextLogState(MENU);
      break;




//*Read date time
    case MCP_READ:
      // get current date time from MCP.
      // set next state
      // short term the tick count will suffice.
      {
      unsigned long long secs = ticks();
      uint8_t hh = secs/3600;
      uint8_t mm = (secs - (hh*3600))/60;
      uint8_t ss = secs - (hh*3600) - (mm*60);

      payload.date.year = 23;
      payload.date.month = 06;
      payload.date.date = 12;
      payload.date.hour = hh;
      payload.date.min = mm;
      payload.date.sec = ss;
      }

      setLogState(SHT_START);
      setNextLogState(SHT_START);
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
        tempResult /= 65535; //this operation honestly sucks man
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

        payload.temp = (int16_t)tempResult;
        payload.relHum = (uint8_t)humResult;

        char messageHolder[32] = {0};
        sprintf(messageHolder, "Temp: %d | RH: %d\r\n", payload.temp, payload.relHum);
        uartPrintString(messageHolder, 32);
      }
      setLogState(SLEEP);
      setNextLogState(SHT_START);
      break;




//*Write logs to EE
    case EE_WRITE:
      // final format data for EE, including a struct
      // write data to EE
      // set next state
      // sleep for an appropriate time

      payload.identifier = SLL_ID;
      payload.num = currentLogIndex;
      payload.AL = 0xC0DE; //placeholder
      payload.nextNode = ((currentLogIndex + 1)<<4);

      EE_write((currentLogIndex<<4), &payload, 16);


      setLogState(SLEEP);
      setNextLogState(EE_READ);
      break;




//*Verify EE data
    case EE_READ:
      // read back EE data from last address written
      // check it matches what we just sent
      // if it does, move onto next state
      // if not, we got an error

      // consider goiong back to write for a few turns.
      break;




//*Write next alarm time to RTC
    case MCP_WRITEALARM: //UNUSED
      // set alarm for RTC
      break;




//*General Sleep state
    case SLEEP:
      // Set up sleep mode
      LPM3;
      break;




//*Full EE Readback
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




//*Full EE Wipe
    case EE_RESET:
      {
        char message[24] = "\r\nEE Wipe Started\r\n";
        uartPrintString(message, 24);
        uint8_t data[32]; //!Need to test the heck outta this bad boy
        uint8_t i;
        for(i = 0; i < 32; i++)
        {
          data[i] = 0xFF;
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

        currentLogIndex = 0; //set these to both indicate a clean EE
        lastLogIndex = 0; 

        setLogState(MENU);
      }
      break;

    default:
      break;
    }
  }
}
