#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include "core.h"

typedef struct 
{
    uint16_t address;
    NODE_PAYLOAD_S data;
} NODE_S;

typedef struct 
{
    uint16_t entry;
    DATE_TIME_S date;
    uint16_t temp;
    uint16_t rHum;
    uint16_t ambLight;
    uint16_t nextNode;
} NODE_PAYLOAD_S;

typedef struct 
{
    uint8_t sec;
    uint8_t min;
    uint8_t hr;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DATE_TIME_S;



#endif
