#include <xc.h>
#include <stdlib.h>
#include "lcd.h"
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
    if(count == 2)
        uart2_print("F\r"); //Search mode
    if(count == 3)
        uart2_print("C,0,801F12B58D2F\r"); //Connect to module
}

char* BLE_parse(char str[])
{
    int i = 0;
    int j = 0;
    char* temp = (char*)malloc(sizeof(str));
    while(str[i] != '\0')
    {
        if(str[i] != '%')
            temp[j++] = str[i];
        i++;
    }
    temp[j] = '\0';
    return temp;
}