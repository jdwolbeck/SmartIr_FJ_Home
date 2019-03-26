#include <xc.h>
#include "initialization.h"
#include "lcd.h"
#include "system.h"

void InitApp()
{
    InitGPIO();
    InitUART();
    InitLCD();
    InitKeypad();
}

void InitGPIO()
{
    LATB = 0;
    //Set direction of RB pins (1 = input | 0 = output)
    TRISB = 0xFFFF;
    //Set pins as digital input pins
    ANSB = 0;
}

void InitUART()
{
    
}

void InitLCD()
{
    // Set direction of all pins to output
    RS_DIR = 0;
    RW_DIR = 0;
    EN_DIR = 0;
    
    D7_DIR = 0;
    D6_DIR = 0;
    D5_DIR = 0;
    D4_DIR = 0;
    
    //Set LCD and clear it
    LCD_begin();
    LCD_clear();
    LCD_mainMenu();
}

void InitKeypad()
{
    //Set keys as inputs
    K1_DIR = 1;
    K2_DIR = 1;
    K3_DIR = 1;
    K4_DIR = 1;
    
    //Enable Interrupt on negative going edge
    IOCNBbits.IOCNB10 = 1;
    IOCNBbits.IOCNB11 = 1;
    IOCNBbits.IOCNB12 = 1;
    IOCNBbits.IOCNB13 = 1;
    
    //Enable Pull-up resistors
    IOCPUBbits.CNPUB10 = 1;
    IOCPUBbits.CNPUB11 = 1;
    IOCPUBbits.CNPUB12 = 1;
    IOCPUBbits.CNPUB13 = 1;
    
    
    //Enabling IOC interrupt
    PADCONbits.IOCON = 1; // IOC interrupt enable
    IOCFB = 0; // Each bits interrupt flag
    IFS1bits.IOCIF = 0; // Interrupt flag
    IPC4bits.IOCIP = 3; // Interrupt priority
    IEC1bits.IOCIE = 1; // Global enable
}