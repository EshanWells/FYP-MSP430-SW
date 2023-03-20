#include "uart.h"

#include <msp430.h>

void initUart(void)
{
    P1DIR |= BIT1 + BIT2;
    P1SEL = BIT1 + BIT2;               // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2;

    UCA0CTL1 |= UCSSEL_2;       // SMCLK
    UCA0BR0 = 8;                // 1MHz 115200
    UCA0BR1 = 0;                // 1MHz 115200
    UCA0MCTL = UCBRS2 + UCBRS0; // Modulation UCBRSx = 5
    UCA0CTL1 &= ~UCSWRST;       // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;            // Enable USCI_A0 RX interrupt
}

void uartPrintString(char* str, uint8_t size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        while (!(IFG2 & UCA0TXIFG));// USCI_A0 TX buffer ready?
        UCA0TXBUF = str[i]; //char to txbuffer
    }
}

/************************************/

#pragma vector=USCIAB0RX_VECTOR
__interrupt void UART_RX_ISR(void)
{
    while (!(IFG2 & UCA0TXIFG)); // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF; // TX -> RXed character
    LED_TGLE;
}