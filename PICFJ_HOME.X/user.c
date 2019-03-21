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

#include "user.h"
#include "gpio.h"
#include "uart.h"

void delay(int delay_index)
{
    int i,j;
    for(i = 2*delay_index; i > 0; i--)
    {
        for(j = 284; j > 0; j--);
    }
}