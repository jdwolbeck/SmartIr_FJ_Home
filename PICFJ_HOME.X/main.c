/******************************************************************************/
// PIC with WiFi (ESP8266) ... Joshua Wolbeck ... ECE 461
/******************************************************************************/

/* Device header file */
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

#include <stdio.h>
#include "user.h"
#include "main.h"
#include "system.h"
#include "esp8266.h"
#include "configuration_bits.h"

int delay_value = 1000; //ms

int main() 
{
    InitApp();

    TRISAbits.TRISA2 = 0;
    ANSAbits.ANSA2 = 0;
    while(1)
    {
        
    }
    return 0;
}
