#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "main.h"
#include "uart.h"
#include "system.h"
#include "bluetooth.h"

BLE_DATA bleData;

void BLE_connect(int count)
{
    if(count == 1)
    {
        uart2_print("$");
        delay(220);
        uart2_print("$$");  //CMD mode
    }
    else if(count == 2)
    {
        uart2_print("F\r"); //Search mode
    }
    else if(count == 3)
    {
        bleData.isConnected = true;
        uart2_print("C,0,801F12B58D2F\r"); //Connect to module
        bleData.packetBuf[0] = '\0';
    }
}

void BLE_parseT1(char str[])
{
    int i = 0, j = 0, k;
    char temp[100];

    while(str[i] != '\0' && str[i] != '%') // go through the string until first thing
        i++;
    
    while(str[i] != '\0')
    {
        k = 0;
        while(str[i] == '%')
            i++;
        
        while(str[i] != '\0' && str[i] != '%')//str[i] != ',')
        {
            temp[k] = str[i];
            k++;
            i++;
        }
//        while(str[i] != '%' && str[i] != '\0')
//            i++;
        
        temp[k] = '\0';
        if(k != 0)
        {
            strcpy(bleData.foundBT[j],temp);
            j++;
        }
    }
    
    while(bleData.foundBT[k][0] != '\0')
    {
        if(!strcmp(bleData.foundBT[k],"801F12B58D2F"))
            BLE_connect(3);
        k++;
    }
}