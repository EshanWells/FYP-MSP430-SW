#ifndef UART_H_
#define UART_H_

#include "core.h"
#include <msp430.h>

void initUart(void);

void uartPrintString(char* str, uint8_t size);

#endif
