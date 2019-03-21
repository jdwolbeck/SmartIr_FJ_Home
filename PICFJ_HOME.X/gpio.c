/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include "gpio.h"

void InitGPIO(void)
{
    LATB = 0;
    //Set direction of RB pins (1 = input | 0 = output)
    TRISB = 0x008B;
    //Set pins as digital input pins
    ANSB = 0;
}