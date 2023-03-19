#ifndef UARTA_H_
#define UARTA_H_

#include <msp430g2553.h>
#include "core.h"

void initUARTA(void);

void UARTSend(unsigned char *TxArray, unsigned char arrayLength);

#endif
