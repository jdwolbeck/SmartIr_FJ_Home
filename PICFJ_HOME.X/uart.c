#include <xc.h>
#define FCY 4000000
#define BAUD_RATE 9600
#include "uart.h"
#include "main.h"
#include "lcd.h"
#include <string.h>

//void InitUART(void)
//{
//    U1MODE = 0x0000;//(0x8008 & ~(1<<15));//0x0000;
//    U2MODE = 0x0000;
//    U1STA = 0x0000;
//    U2STA = 0x0000;
//        
//    RPINR18bits.U1RXR = 3; //Set RB3 as U1RX
//    RPINR19bits.U2RXR = 7; //Set RB7 as U2RX
//    RPOR2bits.RP4R = 3;  //Set RB4 as U1TX
//    RPOR3bits.RP6R = 5; //Set RB6 as U2TX
//    IFS0bits.U1RXIF = 0; //Clear RX interrupt Flag
//    IFS1bits.U2RXIF = 0; //Clear the RX interrupt Flag
//    IPC2bits.U1RXIP = 3; //Priority of RX set to 3
//    IPC7bits.U2RXIP = 3; //Priority of RX set to 3
//    IEC0bits.U1RXIE = 1; //RX interrupt enabled    
//    IEC1bits.U2RXIE = 1; //RX interrupt enabled
//    
//    //Baud_Rate = 9600; Frequency = 4MHz; U2BRG = 25;
//    U1BRG = (((FCY/BAUD_RATE)/16)-1); //Calculate baud rate registers value
//    U2BRG = (((FCY/BAUD_RATE)/16)-1); //Calculate baud rate registers value
//    U1MODEbits.UARTEN = 1;  //UART1 enable 
//    U2MODEbits.UARTEN = 1;  //UART2 enable
//    U1STAbits.UTXEN = 1;    //Enable
//    U2STAbits.UTXEN = 1;    //TX enable
//}

void uart(char RXchar)
{
//    char RXread[100];
//    uart_print("Input: ");
//    while(!U2STAbits.TRMT);
//    U2TXREG = RXchar;
//    
//    switch(RXchar)
//    {
//        case 'c':
//            strcpy(RXread,"AT+CWJAP+\"ASUS 2G\",\"01241991\"\r\n");
//            break;
//        default:
//            strcpy(RXread,"Error\r\n");
//            break;
//    }
//    
//    uart_print("\r\nOutput to ESP8266: ");
//    uart_print(RXread);
    //esp8266_connect("ASUS 2G","01241991");
    U2TXREG = RXchar;
    if(RXchar == 'i')
    {
        uart_print("LCD Initialization and printing of Hello!");
    }
}

void uart_print(char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        while(!U2STAbits.TRMT);
        U2TXREG = str[i++];
    }
}