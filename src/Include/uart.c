/**
 * @file uart.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief barebones HW UART driver using USCIA
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "uart.h"


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
    uint8_t i;
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
    if((getLogState() == SLEEP) && (getNextLogState() == MENU))
    {       
        switch (UCA0RXBUF)
        {
        case 0x31: //1
            {
                setLogState(SHT_START);
                char message[24] = "\r\nLogger Start\r\n";
                uartPrintString(message, 24);
            }
            break;

        case 0x32:
            {
                setLogState(LOG_READBACK_RAW);
            }
            break;
        
        case 0x33:
            //implement some sort of 'are you sure?' here honestly.
            break;

        default:
            setLogState(MENU);
            break;
        }

        _bic_SR_register_on_exit(LPM3_bits);
    } else if (UCA0RXBUF == 0x6D) {
        setLogState(MENU);
        setNextLogState(MENU);
        _bic_SR_register_on_exit(LPM3_bits);
    } else {
        while (!(IFG2 & UCA0TXIFG)); // USCI_A0 TX buffer ready?
        UCA0TXBUF = UCA0RXBUF; // TX -> RXed character
    }
}
