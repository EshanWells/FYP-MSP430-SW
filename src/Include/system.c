#include "system.h"

#include "core.h"

#define F_MCLK 1000000 //macro for MCLK
#define F_SMCLK 1000000 //macro for SMCLK
#define F_ACLK 125000 //macro for ACLK

/**
 * @brief System Init function
 * 
 */
void sysInit(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    _disable_interrupt();

    // Initialize clocks
    initDCOClock(DCO_1MHz);
    //initLFXT1();

    initMCLK(MCLK_DCO, DIV_1);
    initSMCLK(SMCLK_DCO, DIV_1);    
    initACLK(DIV_8); //set clock to 125000
    //! Need a watch crystal to get ACLK working properly. We'll clock it off DCO for now...

    initUARTA();

    _enable_interrupt();
}

/**
 * @brief DCO Clock setup
 * 
 * @param dcoFreq set using DCO_FREQ enum.
 */
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

    __delay_cycles(200); //Safe time to wait for the DCO to stabilise. Can be shortened in a pinch
}

/**
 * @brief start the LFXT oscillator with an external crystal.
 * 
 */
void initLFXT1(void)
{
    BCSCTL3 = 0x00;
    BCSCTL3 |= XCAP_3; //set caps to 12.5pF
}

/**
 * @brief set source and divider for MCLK
 * 
 * @param src 
 * @param div 
 */
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

/**
 * @brief set source for SMCLK
 * 
 * @param src 
 * @param div 
 */
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

/**
 * @brief set source for ACLK
 * 
 * @param div 
 */
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
