#include <xc.h>
#define FCY 4000000
#define BAUD_RATE 9600
#include "uart.h"
#include "main.h"
#include "lcd.h"
#include <string.h>

void uart(char RXchar)
{
    U1TXREG = RXchar;
}

void uart_print(char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        while(!U1STAbits.TRMT);
        U1TXREG = str[i++];
    }
}

void uart2(char RXchar)
{
    U2TXREG = RXchar;
}

void uart2_print(char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        while(!U2STAbits.TRMT);
        U2TXREG = str[i++];
    }
}