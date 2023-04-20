/**
 * @file system.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief header file for system
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <msp430g2553.h>

#include "core.h"

enum DCO_FREQ {
    DCO_1MHz,
    DCO_8MHz,
    DCO_12MHz,
    DCO_16MHz
};

enum DIV_SEL {
    DIV_1,
    DIV_2,
    DIV_4,
    DIV_8
};

enum MCLK_SEL {
    MCLK_DCO,
    MCLK_XT2,
    MCLK_LFXT
};

enum SMCLK_SEL {
    SMCLK_DCO,
    SMCLK_XT2
};

/**
 * @brief System Init function
 *
 */
void sysInit(void);

/**
 * @brief DCO Clock setup
 *
 * @param dcoFreq set using DCO_FREQ enum.
 */
void initDCOClock(enum DCO_FREQ dcoFreq);

/**
 * @brief start the LFXT oscillator with an external watch crystal.
 *
 */
void initLFXT1(void);

/**
 * @brief 
 * 
 */
void initVLOClock(void);

/**
 * @brief set source and divider for MCLK
 *
 * @param src
 * @param div
 */
void initMCLK(enum MCLK_SEL src, enum DIV_SEL div);

/**
 * @brief set source for SMCLK
 *
 * @param src
 * @param div
 */
void initSMCLK(enum SMCLK_SEL src, enum DIV_SEL div);

/**
 * @brief set source for ACLK
 *
 * @param div
 */
void initACLK(enum DIV_SEL div);

#endif
