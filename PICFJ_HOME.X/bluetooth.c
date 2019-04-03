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
    }
}

void BLE_parseT1(char str[])
{
    int i = 0, j = 0, k, l;
    char temp[100];
    char temp2[100];

    while(str[i] != '\0' && str[i] != '%') // go through the string until first thing
    {
        i++;
    }
    
    while(str[i] != '\0')
    {
        k = 0;
        while(str[i] == '%')
        {
            i++;
        }
        
        while(str[i] != '\0' && str[i] != '%')
        {
            temp[k++] = str[i++];
        }
        
        //Do another read through of the device found and strip off MAC addr
        temp[k] = '\0';
        l = 0;
        while(temp[l] != ',')
        {
            temp2[l] = temp[l];
            l++;
        }
        temp2[l] = '\0';
        
        //Only save the MAC address of the found Bluetooth devices
        if(temp[0] != '\0' && temp[0] != '\r')
        {
            strcpy(bleData.foundBT[j++],temp2);
        }
    }
    
    k = 0;
    while(bleData.foundBT[k][0] != '\0')
    {
        if(!strcmp(bleData.foundBT[k],"801F12B58D2F"))
        {
            //strcpy(bleData.sensors[0],bleData.foundBT[k]);
            BLE_connect(3);
        }
        k++;
    }
}

/*void BLE_searchStream(char str[]) 
{
    char temp[12] = "";
    int i = 0, k;

    while (str[i++] != '\0')
    {
        k = 0;
        while((str[k+i] != '\0') && (k < 11))
        {
            temp[k] = str[k+i];
            k++;
        }
        temp[k] = '\0';
        
        if(!strcmp(temp,"STREAM_OPEN"))
        {
            bleData.streamConn = 1;
            uart_print("yeyeyeyyeyeyyeyyyeyeyyeyeyeyettttt");
            bleData.packetIndex = 0;
            bleData.packetBuf[0] = '\0';
        }
    }
}*/

void BLE_searchStream(char str[]) 
{
    int i = 0, k;
    
    while(str[i] != '\0')
    {
//        if(str[i] == 'S')
//        {
//            if(str[i+6] != '\0')
//            {
//                if(str[i+6] == '_')
//                {
//                    HB_LED = 1;
//                    while(1);
//                }
//            }
//            k = 0;
//            while(str[i+k] != '\0' && k < 11)
//            {
//                temp[k] = str[i+k];
//                k++;
//            }
//            temp[k] = '\0';
//            if(!strcmp(temp,"STREAM_OPEN"))
//            {
//                HB_LED = 1;
//                while(1);
//            }
//        }
        i++;
    }
}
