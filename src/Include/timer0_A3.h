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
 * @param delay expressed as multiples of 8 us
 */
void timer0Counter0(uint16_t delay, uint8_t code);

/**
 * @brief start timer
 *
 */
void startTimer(void);

/**
 * @brief stop timer
 *
 */
void stopTimer(void);

/**
 * @brief toggle P1.0
 *
 */
void blinkLED(void);

/**
 * @brief return timer code, as yet unused
 *
 * @return uint8_t code
 */
uint8_t getTimer0Code0(void);

/**
 * @brief set a code for the timer to return, as yet unused
 *
 * @param set code
 */
void setTimer0Code0(uint8_t set);

uint8_t doTickRoutine(void);

#endif
