#include <xc.h>
#include <stdbool.h>
#include "lcd.h"
#include "system.h"

void LCD_begin(void)
{
    
}

void LCD_write(bool rs, bool d7, bool d6, bool d5, bool d4, bool d3, bool d2, bool d1, bool d0)
{
    RS = rs;
    D7 = d7;
    D6 = d6;
    D5 = d5;
    D4 = d4;
    D3 = d3;
    D2 = d2;
    D1 = d1;
    D0 = d0;
    
    EN = 1;
    EN = 0;
}

void LCD_main(void)
{
    //ONE
    LCD_write(0,0,0,1,1,1,0,0,0);
    delay(5);
    
    //TWO
    LCD_write(0,0,0,0,0,1,1,1,1);
    delay(1);
    
    //THREE
    LCD_write(0,0,0,0,0,0,1,1,0);
    delay(1);
    
    //FOUR
    LCD_write(0,1,1,0,0,0,0,1,1);
    delay(1);
    
    //FIVE
    LCD_write(1,0,1,0,0,1,0,0,0);
    delay(1);
    
    //SIX
    LCD_write(1,0,1,1,0,0,1,0,1);
    delay(1);
    
    //SEVEN
    LCD_write(1,0,1,1,0,1,1,0,0);
    delay(1);
    
    //EIGHT
    LCD_write(1,0,1,1,0,1,1,0,0);
    delay(1);
    
    //NINE
    LCD_write(1,0,1,1,0,1,1,1,1);
    delay(1);
}
