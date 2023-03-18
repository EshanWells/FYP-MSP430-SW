#include <msp430.h> 

#include "system.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	sysInit();

	    // Set P1.0 as output
    P1DIR |= BIT0;
    
    while(1) {
        // Toggle P1.0
        P1OUT ^= BIT0;
        
        // Delay for 1 second
        __delay_cycles(16000000);
    }

	return 0;
}
