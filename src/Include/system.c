/**
 * @file system.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief contains inits for system, clock generators and sources. May actually be usable in other projects.
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "system.h"

#include "core.h"

#define F_MCLK 1000000 //macro for MCLK
#define F_SMCLK 1000000 //macro for SMCLK
#define F_ACLK 32768 //macro for ACLK

void sysInit(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    _disable_interrupt();

    initGPIO(); //init GPIO before ports get overwritten??

    // Initialize clocks
    initDCOClock(DCO_1MHz);
    //initLFXT1();
    initVLOClock();

    initMCLK(MCLK_DCO, DIV_1);
    initSMCLK(SMCLK_DCO, DIV_1);
    initACLK(DIV_1); //set clock

    initUart();

    I2C_init();

    _enable_interrupt();
}

void initDCOClock(enum DCO_FREQ dcoFreq)
{
    switch (dcoFreq) {
        case DCO_1MHz:
            DCOCTL = CALDCO_1MHZ;
            BCSCTL1 = CALBC1_1MHZ;
            break;
        case DCO_8MHz:
            DCOCTL = CALDCO_8MHZ;
            BCSCTL1 = CALBC1_8MHZ;
            break;
        case DCO_12MHz:
            DCOCTL = CALDCO_12MHZ;
            BCSCTL1 = CALBC1_12MHZ;
            break;
        case DCO_16MHz:
        default:
            DCOCTL = CALDCO_16MHZ;
            BCSCTL1 = CALBC1_16MHZ;
            break;

    }

    BCSCTL1 |= XT2OFF; //ensure XT2 off.

    __delay_cycles(15); //Safe time to wait for the DCO to stabilise. Can be shortened in a pinch
}

void initLFXT1(void)
{
    BCSCTL3 = 0x00;
    //BCSCTL3 |= XCAP_3; //set caps to 12.5pF
    while (BCSCTL3 & BIT0)
    {
        _NOP(); //wait for LFXT to stabilise.
    }

}

void initVLOClock(void)
{
    BCSCTL3 = 0x00;
    BCSCTL3 |= 0b00100000;
    __delay_cycles(5000);
}

void initMCLK(enum MCLK_SEL src, enum DIV_SEL div)
{
    switch(src)
    {
        case MCLK_DCO:
            //BCSCTL2 &= ~0b11000000; //default state, don't need to touch tbh
            break;
        case MCLK_XT2:
            BCSCTL2 |= SELM_2;
            break;
        case MCLK_LFXT:
            BCSCTL2 |= SELM_3;
            break;
    }

    switch(div)
    {
        case DIV_1:
            //BCSCTL &= 0b00110000; //default state
            break;
        case DIV_2:
            BCSCTL2 |= DIVM_1;
            break;
        case DIV_4:
            BCSCTL2 |= DIVM_2;
            break;
        case DIV_8:
            BCSCTL2 |= DIVM_3;
            break;
    }
}

void initSMCLK(enum SMCLK_SEL src, enum DIV_SEL div)
{
    switch(src)
    {
        case SMCLK_DCO:
            //BCSCTL2 &= ~0b11000000; //default state, don't need to touch tbh
            break;
        case SMCLK_XT2:
            BCSCTL2 |= SELS;
            break;
    }

    switch(div)
    {
        case DIV_1:
            //BCSCTL &= 0b00110000; //default state
            break;
        case DIV_2:
            BCSCTL2 |= DIVS_1;
            break;
        case DIV_4:
            BCSCTL2 |= DIVS_2;
            break;
        case DIV_8:
            BCSCTL2 |= DIVS_3;
            break;
    }
}

void initACLK(enum DIV_SEL div)
{
    switch(div)
    {
        case DIV_1:
            //BCSCTL &= 0b00110000; //default state
            break;
        case DIV_2:
            BCSCTL1 |= DIVA_1;
            break;
        case DIV_4:
            BCSCTL1 |= DIVA_2;
            break;
        case DIV_8:
            BCSCTL1 |= DIVA_3;
            break;
    }
}
