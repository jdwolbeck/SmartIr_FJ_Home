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
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "lcd.h"
#include "uart.h"
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
    
    while(1)
    {
        delay(1000);
        HB_LED = !HB_LED;
        if(showDataEn == 1)
            LCD_dataShow();
        
//        if(!bleData.isConnected)
//        {
//            int k = 0;
//            while(bleData.foundBT[k][0] != '\0')
//            {
//                uart_print(bleData.foundBT[k++]);
//                uart_print("\r\n");
//            }
//            uart_print("\r\n");
//        }
//        else
//        {
            uart_print(bleData.packetBuf);
            uart_print("\r\n");
            uart_print("\r\n");
//        }
    }
    int j;
    for(j = 0; j < MAX; j++)
        free(bleData.foundBT[j]);
    
    return 0;
}
