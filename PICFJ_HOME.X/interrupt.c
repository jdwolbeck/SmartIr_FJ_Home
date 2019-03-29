/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>
#include <stdio.h>
#include "uart.h"
#include "lcd.h"
#include "main.h"
#include <string.h>
#include "system.h"
#include "keypad.h"
#include "bluetooth.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    char RXchar = U1RXREG;
    U1TXREG = RXchar;
    IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
    char RXchar = U2RXREG;
    
    bleData.packetBuf[bleData.packetIndex++] = RXchar;
    
    if(!strcmp(bleData.packetBuf, "CMD>"))
    {
        uart_print(bleData.packetBuf);
        bleData.packetBuf[0] = '\0';
        bleData.packetIndex = 0;
        delay(1000);
        BLE_connect(2);
    }
//    else if(RXchar == '%' && bleData.packetIndex != 0)
//    {
//        bleData.packetSize = bleData.packetIndex;
//        uart_print(bleData.packetBuf);
//        bleData.packetIndex = 0;
//        bleData.packetBuf[0] = '\0';
//    }

    IFS1bits.U2RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _IOCInterrupt(void)
{
    if(IOCFBbits.IOCFB13) // K1 (Top) was pressed
        btnPressed(1);
    else if(IOCFBbits.IOCFB12) // K2 (Top-MID) was pressed
        btnPressed(2);
    else if(IOCFBbits.IOCFB11) // K3 (Bot-MID) was pressed
        btnPressed(3);
    else if(IOCFBbits.IOCFB10) // K4 (Bot) was pressed
        btnPressed(4);
    
    IOCFB = 0; // Clear individual flags
    IFS1bits.IOCIF = 0; // Interrupt flag
}