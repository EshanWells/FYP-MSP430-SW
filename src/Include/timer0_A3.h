/**
 * @file timer0_A3.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief header for Timer0_A3
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef T0A3_H_
#define T0A3_H_

#include "core.h"

/**
 * @brief
 *
 * @param delay expressed as multiples of ???
 */
void timer0Counter0(uint16_t delay);

/**
 * @brief start timer
 *
 */
void startTimer(void);

/**
 * @brief stop timer
 *
 */
void stopTimer0(void);

/**
 * @brief toggle P1.0
 *
 */
void blinkLED(void);

#endif
