#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "main.h"
#include "uart.h"
#include "system.h"
#include "bluetooth.h"
#include "initialization.h"

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

bool BLE_searchStr(char key[], char str[])
{
    char temp[strlen(key)];
    int i = strlen(key) - 1, j, k = 0;
    
    while(str[i++] != '\0')
    {
        for(j = 0; j < strlen(key); j++)
        {
            temp[j] = str[j+k];
        }
        temp[j] = '\0';
        if(!strcmp(temp,key))
            return true;
        k++;
    }
    return false;
}

void BLE_update(void)
{
    bool found = false;
    if(bleData.packetBuf[bleData.packetIndex-2] == '>' && !bleData.isConnected)
    {
        BLE_connect(2);
    }
    
    if(bleData.packetBuf[bleData.packetIndex-2] == '\r' && !bleData.isConnected)
    {
        BLE_parseT1(bleData.packetBuf);
    }
    
    if(bleData.streamConn)
    {
        if(BLE_parseData(bleData.packetBuf))
        {
            memset(bleData.packetBuf,'\0',PACKET_LEN);
            bleData.packetIndex = 0;
        }
    }
    
    found = BLE_searchStr("DISCONNECT",bleData.packetBuf);
    if(found && !bleData.streamConn)
    {      
        uart_print("\r\n--DISCONNECT--\r\n");
        uart2_print("R,1\r");
        delay(2000);
    }

    found = BLE_searchStr("STREAM_OPEN",bleData.packetBuf);
    if(found && !bleData.streamConn)
    {
        memset(bleData.packetBuf,'\0',PACKET_LEN);
        bleData.packetIndex = 0;
        uart_print("\r\n--STREAM OPEN--\r\n");
        delay(500);
        bleData.streamConn = true;
    }
    
    found = BLE_searchStr("REBOOT",bleData.packetBuf);
    if(found)
    {
        InitBluetooth();
        uart_print("\r\n--REBOOT--\r\n");
        delay(1000);
    }
    
    bleData.dataReceived = false;
}

bool BLE_parseData(char str[])
{
    int i,j,k,n;
    int count=0;
    
    for(i = 0; bleData.packetBuf[i] != '\0'; i++)
    {
        if(bleData.packetBuf[i] == ',')
            count++;
    }
    
    if(count < 3)
        return false;
    
//    j/k : are the buffer index
//    i : represents a particular data
//    n : is the specific data's value index
    
    k = 0;
    for(i = 0; i < 3; i++)
    {
        n = 0;
        for(j = k; bleData.packetBuf[j] != ','; j++)
        {
            bleData.data[i][n++] = bleData.packetBuf[j];
            k++;
        }
        k++;
    }
    return true;
}