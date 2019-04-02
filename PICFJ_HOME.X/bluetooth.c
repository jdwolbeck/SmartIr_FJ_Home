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
        uart2_print("C,0,801F12B58D2F\r"); //Connect to module
}

char* BLE_parse(char str[])
{
    int i = 0;
    int k;
    int j = 0;
    int good;
    char* pstr[10];
    char temp[50];
    
    //allocating memory for array of character pointers
    for(i = 0; i < 10; i++)
        pstr[i]=malloc(50);
    i = 0;
    
    while(str[i] != '\0') // Go until end of buffer
    {
        temp[0] = '\0';
        good = 1;
        k = 0;
        if(j > 1) //j = 0,1
            i++;
        
        while(str[i] != '%')
        {
            if(str[i] == ',')
            {
                good = 0;
                temp[k] = '\0';
            }
            if(good)
            {
                temp[k++] = str[i];
            }
            i++;
        }

        pstr[j] = temp;
        if(strcmp(temp,"801F12B58D2F"))
        {
            bleData.packetIndex = 0;
            bleData.packetBuf[0] = '\0';
            BLE_connect(3);
        }
        j++;
    }
    
    return pstr[0];
}

char* BLE_parseT1(char str[])
{
    int i = 0;
    char temp[50];
    char* pstr;
    
    while(str[i] != '%')
    {
        temp[i] = str[i];
    }
    pstr = "hey";
    return &pstr;
}