#ifndef SYSTEM_H
#define SYSTEM_H

#include <msp430g2553.h>

#include "core.h"

enum DCO_FREQ {
    DCO_1MHz,
    DCO_8MHz,
    DCO_12MHz,
    DCO_16MHz
};

void sysInit(void);
void initDCOClock(enum DCO_FREQ dcoFreq);

#endif
