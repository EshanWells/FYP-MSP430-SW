/**
 * @file core.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief key includes for project.
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */



#ifndef FYP_CORE_H_
#define FYP_CORE_H_


#include <msp430.h>
#include "msp430g2553.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "system.h"
#include "gpio.h"
#include "timer0_A3.h"
#include "timer1_A3.h"
#include "uart.h"
#include "I2C.h"
#include "EE.h"
#include "SHT40.h"
#include "RTC.h"

typedef enum
{
    STARTUP = 0,
    MENU,
    MCP_READ,
    SHT_START,
    SHT_READ,
    EE_WRITE,
    EE_READ,
    MCP_WRITEALARM,
    SLEEP,
    LOG_READBACK_RAW,
    GENERAL_ERROR,
    EE_ERROR,
    I2C_ERROR,
    EE_RESET
}LOG_FSM;

extern volatile LOG_FSM logState;

extern volatile LOG_FSM nextLogState;

void setLogState(LOG_FSM set);

LOG_FSM getLogState(void);

void setNextLogState(LOG_FSM set);

LOG_FSM getNextLogState(void);

#endif /* SRC_INCLUDE_CORE_H_ */
