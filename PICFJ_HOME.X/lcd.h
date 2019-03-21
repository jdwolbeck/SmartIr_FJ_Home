#include <xc.h>
#include <stdbool.h>

#define RS LATBbits.LATB5
#define EN LATBbits.LATB2
#define D7 LATBbits.LATB8
#define D6 LATBbits.LATB9
#define D5 LATBbits.LATB10
#define D4 LATBbits.LATB11
#define D3 LATBbits.LATB12
#define D2 LATBbits.LATB13
#define D1 LATBbits.LATB14
#define D0 LATBbits.LATB15

void InitLCD();
void LCD_begin();
void LCD_write(bool,bool,bool,bool,bool,bool,bool,bool,bool);
void LCD_main();