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

#endif
