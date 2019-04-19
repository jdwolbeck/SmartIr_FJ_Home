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
bool autoEn = false;
bool showDataEn = false;
bool tryingConn = false;

int main() 
{
    InitApp();
    delay(100);
    uart2_print("R,1\r"); //Used to reboot bluetooth on startup
    
    while(1)
    {
        delay(250);
        HB_LED = !HB_LED;
        
        if(bleData.dataReceived)
            BLE_update();
        
        if(showDataEn)
            LCD_dataShow();
        
        if(!bleData.isConnected)
        {
            if(!tryingConn)
            {
                tryingConn = true;
                BLE_connect(1);
            }
            int k = 0;
            while(bleData.foundBT[k][0] != '\0')
            {
                uart_print(bleData.foundBT[k++]);
                uart_print("\r\n");
            }
            uart_print("\r\n");
        }
        else
        {
            int k = 0;
            while(bleData.data[k][0] != '\0')
            {
                uart_print(bleData.data[k++]);
                uart_print(" ");
            }
            uart_print("\r\n");
        }
    }
    int j;
    for(j = 0; j < MAX; j++)
        free(bleData.foundBT[j]);
    
    return 0;
}
