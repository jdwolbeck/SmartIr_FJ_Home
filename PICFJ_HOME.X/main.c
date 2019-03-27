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
#include <stdbool.h>
#include "main.h"
#include "lcd.h"
#include "system.h"
#include "keypad.h"
#include "bluetooth.h"
#include "initialization.h"
#include "configuration_bits.h"

int delay_value = 1000; //ms
int currentMenu = 0;
int autoEn = false;
int showDataEn = 0;

int main() 
{
    InitApp();
    
    int index = 0;
    char temp[5];
    temp[0] = '\0';
    
    bleData.packetEOT = false;
    bleData.packetIndex = 0;

    while(1)
    {
        delay(250);
        HB_LED = !HB_LED;
        if(showDataEn)
            LCD_dataShow();
        if(bleData.packetEOT)
        {
            temp[0] = index + '0';
            temp[1] = '\0';
            LCD_clear();
            LCD_display(temp);
            bleData.packetEOT = false;
            index++;
        }
    }
    return 0;
}
