#include <xc.h>
#include "lcd.h"
#include "uart.h"
#include "system.h"
#include "bluetooth.h"

BLE_DATA bleData;

void BLE_connect(void)
{
    uart2_print("$");
    uart2_print("$$");
    uart2_print("F\r");
    delay(2500);
    uart2_print("C,0,801F12B58D2F\r");
    LCD_clear();
    LCD_display("Sent");
}
