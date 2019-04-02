#include <xc.h>
#include <stdlib.h>
#include "initialization.h"
#include "lcd.h"
#include "system.h"
#include "bluetooth.h"

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
    
    HB_LED_DIR = 0;
}

void InitUART()
{
    //Bluetooth reset pin
//    TRISAbits.TRISA0 = 0;
//    ANSAbits.ANSA0 = 0;
//    LATAbits.LATA0 = 0;
//    delay(10);
//    LATAbits.LATA0 = 1;
    
    //UART 1 (Regular/ESP)
    U1MODE = 0x0000;//(0x8008 & ~(1<<15));
    U1STA = 0x0000;
    
    TRISBbits.TRISB3 = 0;   //Set RB3 (TX) as output
    TRISBbits.TRISB2 = 1;   //Set RB2 (RX) as input
    RPINR18bits.U1RXR = 2;  //Set RB2 as U1RX
    RPOR1bits.RP3R = 3;     //Set RB3 as U1TX (3)   
    
    IFS0bits.U1RXIF = 0; //Clear RX interrupt Flag
    IPC2bits.U1RXIP = 3; //Priority of RX set to 3
    IEC0bits.U1RXIE = 1; //RX interrupt enabled   
    
    //Baud_Rate = 9600; Frequency = 4MHz; U1BRG = 25;
    U1BRG = (((FCY/BAUD_RATE)/16)-1); //Calculate baud rate registers value
    
    U1MODEbits.UARTEN = 1;  //UART1 enable
    U1STAbits.UTXEN = 1;    //UART1 TX Enable
    
    //UART 2 (Bluetooth))
    bleData.packetEOT = false;
    bleData.isConnected = false;
    bleData.count = 0;
    bleData.packetIndex = 0;
    bleData.packetBuf[0] = '\0';
    
    U2MODE = 0x0000;
    U2STA = 0x0000;
    
    TRISBbits.TRISB4 = 0;   //Set RB4 (TX) as output
    TRISBbits.TRISB5 = 1;   //Set RB5 (RX) as input
    RPINR19bits.U2RXR = 5; //Set RB5 as U2RX
    RPOR2bits.RP4R = 5; //Set RB4 (4) as U2TX (5))
    
    IFS1bits.U2RXIF = 0; //Clear the RX interrupt Flag
    IPC7bits.U2RXIP = 3; //Priority of RX set to 3
    IEC1bits.U2RXIE = 1; //RX interrupt enabled
    
    //Baud_Rate = 9600; Frequency = 4MHz; U2BRG = 25;
    U2BRG = (((FCY/BAUD_RATE)/16)-1); //Calculate baud rate registers value
    
    U2MODEbits.UARTEN = 1;  //UART2 enable
    U2STAbits.UTXEN = 1;    //TX enable
}

void InitLCD()
{
    // Set direction of all pins to output
    RS_DIR = 0;
    //RW_DIR = 0; //Unused (GND))
    EN_DIR = 0;
    
    D7_DIR = 0;
    D6_DIR = 0;
    D5_DIR = 0;
    D4_DIR = 0;
    
    //Set LCD and clear it
    LCD_begin();
    LCD_clear();
    LCD_blink(1);
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