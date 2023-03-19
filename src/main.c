#include <msp430.h> 

#include "core.h"
#include "gpio.h"

/**
 * main.c
 */
int main(void)
{
	sysInit();
	initGPIO();

	timer0Counter0(65535);
	while(1){
	    LPM1;
	}
}

