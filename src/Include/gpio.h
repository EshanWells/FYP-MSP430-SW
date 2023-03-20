#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <msp430g2553.h>

#include "core.h"

void initGPIO(void);

#define LED_HIGH P1OUT |= BIT0
#define LED_LOW P1OUT &= ~BIT0
#define LED_TGLE P1OUT ^= BIT0

#define UART_1_HIGH P2OUT |= BIT2
#define UART_1_LOW P2OUT &= ~BIT2
#define UART_1_TGLE P2OUT ^= BIT2

#define UART_2_HIGH P2OUT |= BIT3
#define UART_2_LOW P2OUT &= ~BIT3
#define UART_2_TGLE P2OUT ^= BIT3

#define EE_1_HIGH P2OUT |= BIT4
#define EE_1_LOW P2OUT &= ~BIT4
#define EE_1_TGLE P2OUT ^= BIT4

#endif
