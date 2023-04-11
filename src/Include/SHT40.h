/**
 * @file SHT40.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SHT40_H_
#define SHT40_H_

#include "core.h"

#define SHT40_ADDR 0x44

#define T_MULT 10
#define H_MULT 2 //unit of 0.5% ticks?

typedef enum
{
    TRH_HIGH = 0xFD,
    TRH_MID  = 0xF6,
    TRH_LOW  = 0xE0,
    SER_NUM  = 0x89,
    SOFT_RST = 0x94,
    H200_1_0 = 0x39,
    H200_0_1 = 0x32,
    H110_1_0 = 0x2F,
    H110_0_1 = 0x24,
    H020_1_0 = 0x1E,
    H020_0_1 = 0x15
} SHT_COMMAND_E;

typedef struct 
{
    int16_t temp;
    uint8_t rHum;
}SHT_RESULT_S;

void SHT_sendCommand(SHT_COMMAND_E command);

uint16_t SHT_getSerialNumber(void);

SHT_RESULT_S SHT_getMedReading(void);

#endif
