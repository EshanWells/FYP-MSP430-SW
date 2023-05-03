/**
 * @file datalogger.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include "core.h"

#define SLL_ID (uint8_t)0x5A

typedef struct 
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} __attribute__((packed)) DATETIME_S;

typedef struct
{
    uint8_t high;
    uint8_t low;
} __attribute__((packed)) TWOBYTEHL_S;

typedef struct
{
    uint8_t identifier;     //1
    uint16_t num;        //3
    DATETIME_S date;        //9
    uint16_t temp;       //11
    uint8_t relHum;         //12
    uint16_t AL;         //14
    uint16_t nextNode;   //16
} __attribute__((packed)) PAYLOAD_S;

typedef struct 
{
    TWOBYTEHL_S nodeAddress;
    PAYLOAD_S data;
} SLL_NODE_S;

#endif
