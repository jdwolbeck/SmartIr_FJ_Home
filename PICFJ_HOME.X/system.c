/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include "system.h"
#include "gpio.h"
#include "uart.h"
#include "lcd.h"

//void InitClock(void)
//{
//    // CPDIV 1:1; PLLEN disabled; DOZE 1:8; RCDIV FRC; DOZEN disabled; ROI disabled; 
//    CLKDIV = 0x3000;
//    // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 
//    OSCTUN = 0x0000;
//    // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 
//    REFOCONL = 0x0000;
//    // RODIV 0; 
//    REFOCONH = 0x0000;
//    // ROTRIM 0; 
//    REFOTRIML = 0x0000;
//    // DCOTUN 0; 
//    DCOTUN = 0x0000;
//    // DCOFSEL 8; DCOEN disabled; 
//    DCOCON = 0x0700;
//    // DIV 0; 
//    OSCDIV = 0x0000;
//    // TRIM 0; 
//    OSCFDIV = 0x0000;
//    // CF no clock failure; NOSC FRC; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
//    __builtin_write_OSCCONH((uint8_t) ((0x0000 >> _OSCCON_NOSC_POSITION) & 0x00FF));
//    __builtin_write_OSCCONL((uint8_t) (0x0000 & 0x00FF));
//}

void InitApp(void)
{
    InitGPIO();
    InitUART();
}