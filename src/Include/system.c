#include "system.h"
#include "core.h"

void sysInit(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Initialize DCO clock
    initDCOClock(DCO_16MHz);

    // Insert any additional initialization code here
}



void initDCOClock(enum DCO_FREQ dcoFreq)
{
    uint16_t freqSetting;

    switch (dcoFreq) {
        case DCO_1MHz:
            freqSetting = CALBC1_1MHZ;
            DCOCTL = CALDCO_1MHZ;
            BCSCTL1 = CALBC1_1MHZ;
            break;
        case DCO_8MHz:
            freqSetting = CALBC1_8MHZ;
            DCOCTL = CALDCO_8MHZ;
            BCSCTL1 = CALBC1_8MHZ;
            break;
        case DCO_12MHz:
            freqSetting = CALBC1_12MHZ;
            DCOCTL = CALDCO_12MHZ;
            BCSCTL1 = CALBC1_12MHZ;
            break;
        case DCO_16MHz:
        default:
            freqSetting = CALBC1_16MHZ;
            DCOCTL = CALDCO_16MHZ;
            BCSCTL1 = CALBC1_16MHZ;
            break;
    }
}
