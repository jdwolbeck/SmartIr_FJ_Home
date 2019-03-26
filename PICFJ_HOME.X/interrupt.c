/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#if defined (__XC16__)
    #include <xc.h>
#elif defined (__C30__)
    #if defined(__PIC24E__)
        #include <p24Fxxxx.h>
    #elif defined (__PIC24F__) || defined (__PIC24FK__)
        #include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
        #include <p24Hxxxx.h>
    #endif
#endif

#include "uart.h"
#include "keypad.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    IFS0bits.U1RXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
    char RXread = U2RXREG;
    uart(RXread);
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