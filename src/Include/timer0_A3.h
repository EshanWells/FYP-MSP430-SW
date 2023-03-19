#ifndef T0A3_H_
#define T0A3_H_

#include "core.h"

void timer0Counter0(uint16_t delay, uint8_t code);

void blinkLED(void);

uint8_t getTimer0Code0(void);
void setTimer0Code0(uint8_t set);

#endif
