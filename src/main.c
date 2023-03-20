#include <msp430.h> 

#include "core.h"
#include "gpio.h"

/**
 * main.c
 */
int main(void)
{
	sysInit();

	timer0Counter0(16384,1);

	__bis_SR_register(LPM3_bits + GIE);

	while(1);
}
