/**
 * @file gpio.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief GPIO header with FYP specific macros
 * @version 0.1
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <msp430g2553.h>

#include "core.h"

/**
 * @brief initialise gpio pins, without consideration for other peripherals.
 * 
 */
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
