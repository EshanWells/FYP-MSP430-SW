#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <msp430g2553.h>

#include "core.h"

void initGPIO(void);
void setPinHigh(uint8_t port, uint8_t pin);
void setPinLow(uint8_t port, uint8_t pin);
void togglePin(uint8_t port, uint8_t pin);
uint8_t readPin(uint8_t port, uint8_t pin);

#endif