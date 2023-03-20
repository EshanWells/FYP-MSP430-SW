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

enum DIV_SEL {
    DIV_1,
    DIV_2,
    DIV_4,
    DIV_8
};

enum MCLK_SEL {
    MCLK_DCO,
    MCLK_XT2,
    MCLK_LFXT
};

enum SMCLK_SEL {
    SMCLK_DCO,
    SMCLK_XT2
};


void sysInit(void);
void initDCOClock(enum DCO_FREQ dcoFreq);
void initLFXT1(void);

void initMCLK(enum MCLK_SEL src, enum DIV_SEL div);
void initSMCLK(enum SMCLK_SEL src, enum DIV_SEL div);
void initACLK(enum DIV_SEL div);

#endif
