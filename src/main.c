#include <msp430.h> 

#include "core.h"
#include "gpio.h"
/*
 * main.c
*/

uint8_t rxedData[] = {0, 0, 0};

int main(void)
{
	sysInit();

	timer0Counter0(16384,1);

	__bis_SR_register(GIE);

  I2C_setSlaveAddr(0x50);

  //I really hope i fixed this.

	while(1)
	{
	    //_nop();
      I2C_txInit(); //set transmit mode
      I2C_setStart(); //send start and address
      I2C_transmit(0x11); //high address
      I2C_transmit(0x22); //low address
      I2C_setStop();

      __delay_cycles(1000);
	}
}
