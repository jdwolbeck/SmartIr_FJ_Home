#include <xc.h>
#include <string.h>
#include <stdbool.h>
#include "lcd.h"
#include "main.h"
#include "uart.h"
#include "system.h"
#include "bluetooth.h"

//////////////////////////////////////////////////////////////
/*                 Basic Operations                         */
//////////////////////////////////////////////////////////////

void LCD_begin(void)
{
    delay(15);
    
    //8-bit mode initialization
    //Function Set: (Command, -, -, 1, 8-bit, 2-line, 5x8, -, -)
    //LCD_write(0,0,0,1,1,1,0,0,0);
    
    //4-bit mode initialization
    //This starts up in 8-bit mode (required)
    LCD_write(0,0,0,1,1);
    delay(10);
    LCD_write(0,0,0,1,1);
    delay(5);
    LCD_write(0,0,0,1,1);
    delay(10);
    LCD_write(0,0,0,1,0);
    delay(5);
    //This actually sets it into 4-bit mode
    LCD_write(0,0,0,1,0);
    delay(10);
    LCD_write(0,1,0,0,0);
    delay(5);
    
    //Display/Cursor: (Command, - , -, -, -, 1, DisplayOn, CursorOn, BlinkingOn)
    //LCD_write(0,0,0,0,0,1,1,1,1);
    LCD_write(0,0,0,0,0); // Higher nibble
    LCD_write(0,1,1,1,1); // Lower nibble
    delay(5);
    
    //Entry Mode: (Command, -, -, -, -, -, 1, Increment(Right), No Shift))
    //LCD_write(0,0,0,0,0,0,1,1,0);
    LCD_write(0,0,0,0,0);
    LCD_write(0,0,1,1,0);
    delay(5);
}

void LCD_clear(void)
{
    //Clear Display
    //LCD_write(0,0,0,0,0,0,0,0,1);
    LCD_write(0,0,0,0,0);
    LCD_write(0,0,0,0,1);
    delay(5);
}

void LCD_home(void)
{
    //Return Home
    //LCD_write(0,0,0,0,0,0,0,1,0);
    LCD_write(0,0,0,0,0);
    LCD_write(0,0,0,1,0);
    delay(5);
}

void LCD_firstLine(void)
{
    //LCD_write(0,1,0,0,0,0,0,0,0);
    LCD_write(0,1,0,0,0);
    LCD_write(0,0,0,0,0);
    delay(5);
}

void LCD_secondLine(void)
{
    //LCD_write(0,1,1,0,0,0,0,0,0);
    LCD_write(0,1,1,0,0);
    LCD_write(0,0,0,0,0);
    delay(5);
}

void LCD_blink(bool state)
{
    if(state) //Display ON, Blinking ON
    {
        //LCD_write(0,0,0,0,0,1,1,1,1);
        LCD_write(0,0,0,0,0);
        LCD_write(0,1,1,1,1);
        delay(5);
    }
    else //Display ON, Cursor OFF
    {
        //LCD_write(0,0,0,0,0,1,1,0,0);
        LCD_write(0,0,0,0,0);
        LCD_write(0,1,1,0,0);
        delay(5);
    }
}

void LCD_display(char str[])
{       
    bool d7, d6, d5, d4;
    
    int i = 0;
    int j;
    while(str[i] != '\0')
    {
        for(j = 0; j < 2; j++)
        {
            if(j == 0)
            {
                d7 = str[i] & 0x80;
                d6 = str[i] & 0x40;
                d5 = str[i] & 0x20;
                d4 = str[i] & 0x10;
            }
            else
            {
                d7 = str[i] & 0x08;
                d6 = str[i] & 0x04;
                d5 = str[i] & 0x02;
                d4 = str[i++] & 0x01;
            }
            LCD_write(1,d7,d6,d5,d4);
            delay(5);
        }
    }
}

void LCD_write(bool rs, bool d7, bool d6, bool d5, bool d4)
{
    RS = rs;
    //RW = 0; //Unused
    D7 = d7;
    D6 = d6;
    D5 = d5;
    D4 = d4;
    
    EN = 1;
    EN = 0;
}

void LCD_read(bool rs, bool d7, bool d6, bool d5, bool d4)
{
    RS = rs;
    //RW = 1; //Unimplemented
    D7 = d7;
    D6 = d6;
    D5 = d5;
    D4 = d4;
    
    EN = 1;
    EN = 0;
}

//////////////////////////////////////////////////////////////
/*                    MENU CODE                             */
//////////////////////////////////////////////////////////////

void LCD_mainMenu(void)
{
    currentMenu = MAIN_MENU;
    LCD_clear();
    LCD_display("1.Water   2.Data");
    LCD_secondLine();
    LCD_display("3.WiFi    4.More");
    LCD_blink(0);
}

void LCD_waterMenu(void)
{
    currentMenu = WATER_MENU;
    LCD_clear();
    LCD_display("1.ON      2.OFF");
    LCD_secondLine();
    LCD_display("3.Auto    4.Back");
}

void LCD_dataMenu(void)
{
    currentMenu = DATA_MENU;
    LCD_clear();
    LCD_display("1.Show    2.Hide");
    LCD_secondLine();
    LCD_display("3.N/A     4.Back");
}

void LCD_wifiMenu(void)
{
    currentMenu = WIFI_MENU;
    LCD_clear();
    LCD_display("1.Show 2.Connect");
    LCD_secondLine();
    LCD_display("3.Conn?   4.Back");
}

void LCD_moreMenu(void)
{
    currentMenu = MORE_MENU;
    LCD_clear();
    LCD_display("1.Setup   2.N/A");
    LCD_secondLine();
    LCD_display("3.Info    4.Back");
}

void LCD_wifiConnectMenu(void)
{
    currentMenu = WIFI_CONN_MENU;
    LCD_clear();
    LCD_display("1.Net1    2.Net2");
    LCD_secondLine();
    LCD_display("3.Net3    4.Back");
}

void LCD_setupMenu(void)
{
    currentMenu = SETUP_MENU;
    LCD_clear();
    LCD_display("1.View 2.Connect");
    LCD_secondLine();
    LCD_display("3.N/A    4.Back");
}
//////////////////////////////////////////////////////////////
/*                  Extra Functions                         */
//////////////////////////////////////////////////////////////

void LCD_waterOn(void)
{
    LCD_secondLine();
    LCD_display("                ");
    LCD_secondLine();
    LCD_display("Watering Enabled");
    delay(3000);
    LCD_waterMenu();
}

void LCD_waterOff(void)
{
    LCD_secondLine();
    LCD_display("                ");
    LCD_secondLine();
    LCD_display("Water shut down!");
    delay(3000);
    LCD_waterMenu();
}

void LCD_waterAuto(void)
{
    autoEn = !autoEn;
    if(autoEn)
    {
        LCD_firstLine();
        LCD_display("                ");
        LCD_firstLine();
        LCD_display("Auto-water: ON");
        delay(3000);
        LCD_waterMenu();
    }
    else
    {
        LCD_firstLine();
        LCD_display("                ");
        LCD_firstLine();
        LCD_display("Auto-water: OFF");
        delay(3000);
        LCD_waterMenu();
    }
}

void LCD_dataShow(void)
{
    LCD_clear();
    LCD_display("Temp Lux Moistur");
    LCD_secondLine();
    while(showDataEn == 1)
    {
        LCD_display("                ");
        LCD_secondLine();
        LCD_display("100.0F 1023 100%");
        delay(250);
        LCD_secondLine();
    }
    if(!showDataEn)
        LCD_dataMenu();
    else
        LCD_mainMenu();
}

void LCD_wifiShow(void)
{
    LCD_clear();
    LCD_secondLine();
    LCD_display("1. Network1");
    delay(1500);
    LCD_clear();
    LCD_display("1. Network1");
    LCD_secondLine();
    LCD_display("2. Network2");
    delay(1500);
    LCD_clear();
    LCD_display("2. Network2");
    LCD_secondLine();
    LCD_display("3. Network3");
    delay(1500);
    LCD_clear();
    LCD_display("3. Network3");
    delay(1500);
    LCD_clear();
    delay(1000);
    LCD_wifiMenu();
}

void LCD_wifiSelect(int netID)
{
    switch(netID)
    {
        case 1:
            LCD_clear();
            LCD_display("Network 1");
            LCD_secondLine();
            LCD_display("selected...");
            delay(2000);
            LCD_wifiMenu();
            break;
        case 2:
            LCD_clear();
            LCD_display("Network 2");
            LCD_secondLine();
            LCD_display("selected...");
            delay(2000);
            LCD_wifiMenu();
            break;
        case 3:
            LCD_clear();
            LCD_display("Network 3");
            LCD_secondLine();
            LCD_display("selected...");
            delay(2000);
            LCD_wifiMenu();
            break;
        default:
            break;
    }
}

void LCD_wifiIsConnected(void)
{
    LCD_clear();
    LCD_display("Coming Soon");
    delay(1500);
    LCD_wifiMenu();
}

void LCD_infoMenu(void)
{
    LCD_clear();
    LCD_display("1=>Top 2=>Top-Md");
    LCD_secondLine();
    LCD_display("3=>Bot-Md 4=>Bot");
    delay(2500);
    LCD_moreMenu();
}

void LCD_bleShow(void)
{
    char temp[STR_LEN];
    int j = 0, ind = 1;
    char index[3];
    index[0] = ind + '0';
    index[1] = '.';
    index[2] = '\0';
    
    while(bleData.foundBT[j][0] != '\0')
    {
        if(!j)
        {
            LCD_clear();
            strcpy(temp,bleData.foundBT[j]);
            temp[16] = '\0';
            LCD_secondLine();
            LCD_display(index);
            LCD_display(temp);
            delay(750);
            j++;
            ind++; //Used for indexing the BT module
        }
        else
        {
            LCD_clear();
            strcpy(temp,bleData.foundBT[j-1]);
            temp[16] = '\0';
            LCD_display(temp);
            LCD_secondLine();
            
            strcpy(temp,bleData.foundBT[j]);
            temp[16] = '\0';
            LCD_display(temp);
            delay(750);
            j++;
        }
    }
    LCD_clear();
    strcpy(temp,bleData.foundBT[j-1]);
    temp[16] = '\0';
    LCD_display(temp);
    delay(750);
            
    LCD_setupMenu();
}

void LCD_bleConnect(void)
{
    LCD_clear();
    LCD_display("Connecting in");
    LCD_secondLine();
    LCD_display("1");
    delay(1000);
    LCD_setupMenu();
    BLE_connect(1);
}