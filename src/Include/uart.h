/**
 * @file uart.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief header for UART using USCIA
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UART_H_
#define UART_H_

#include "core.h"
#include <msp430.h>

/**
 * @brief UART initialise
 *
 */
void initUart(void);

/**
 * @brief simple print string to UART, good for debug
 *
 * @param str pass the array without [], don't overthink this one
 * @param size How many bytes/chars long, where stuff like \n is a byte too.
 */
void uartPrintString(char* str, uint8_t size);

#endif
