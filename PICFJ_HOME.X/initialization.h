#include <xc.h>

#define FCY 4000000
#define BAUD_RATE 9600

#define HB_LED_DIR TRISAbits.TRISA4

#define RS_DIR TRISBbits.TRISB15
//#define RW_DIR TRISBbits.TRISB5 //UNUSED
#define EN_DIR TRISBbits.TRISB14
#define D7_DIR TRISBbits.TRISB6
#define D6_DIR TRISBbits.TRISB7
#define D5_DIR TRISBbits.TRISB8
#define D4_DIR TRISBbits.TRISB9  

#define K1_DIR TRISBbits.TRISB13
#define K2_DIR TRISBbits.TRISB12
#define K3_DIR TRISBbits.TRISB11
#define K4_DIR TRISBbits.TRISB10

void InitApp(void);
void InitGPIO(void);
void InitUART(void);
void InitLCD(void);
void InitKeypad(void);
void InitBluetooth(void);