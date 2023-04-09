#ifndef SHT40_H_
#define SHT40_H_

#include "core.h"

#define SHT40_ADDR 0x44

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

void SHT_sendCommand(SHT_COMMAND_E command);

uint16_t SHT_getSerialNumber(void)

#endif
