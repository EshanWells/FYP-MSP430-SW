#include "gpio.h"
#include "core.h"

void initGPIO(void)
{
    // Set P1.0 and P1.6 as outputs, P1.3 as input
    P1DIR |= BIT0;
    P1DIR &= ~BIT3;
    
    // Set P1.3 to use pull-up resistor
    P1REN |= BIT3;
    P1OUT |= BIT3;
}

void setPinHigh(uint8_t port, uint8_t pin)
{
    switch(port) {
        case 1:
            P1OUT |= pin;
            break;
        case 2:
            P2OUT |= pin;
            break;
        default:
            break;
    }
}

void setPinLow(uint8_t port, uint8_t pin)
{
    switch(port) {
        case 1:
            P1OUT &= ~pin;
            break;
        case 2:
            P2OUT &= ~pin;
            break;
        default:
            break;
    }
}

void togglePin(uint8_t port, uint8_t pin)
{
    switch(port) {
        case 1:
            P1OUT ^= pin;
            break;
        case 2:
            P2OUT ^= pin;
            break;
        default:
            break;
    }
}

uint8_t readPin(uint8_t port, uint8_t pin)
{
    uint8_t result = 0;
    
    switch(port) {
        case 1:
            result = P1IN & pin;
            break;
        case 2:
            result = P2IN & pin;
            break;
        default:
            break;
    }
    
    return result;
}
