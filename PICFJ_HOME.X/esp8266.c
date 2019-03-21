#include <xc.h>
#include "esp8266.h"
#include "main.h"
#include <stdbool.h>

void esp8266_print(char RXread[])
{
    int i = 0;
    while(RXread[i] != '\0')
    {
        while(!U1STAbits.TRMT);
        U1TXREG = RXread[i++];
    }
}

unsigned char esp8266_connect(char ssid[], char pass[]) {
    esp8266_print("AT+CWJAP=\"");
    esp8266_print(ssid);
    esp8266_print("\",\"");
    esp8266_print(pass);
    esp8266_print("\"\r\n");
    //return esp8266_waitResponse();
    return 'a';
}

//unsigned char esp8266_waitResponse(void) {
//    unsigned char so_far[6] = {0,0,0,0,0,0};
//    unsigned const char lengths[6] = {2,5,4,9,6,6};
//    char string1[15] = "OK";
//    char string2[15] = "ready";
//    char string3[15] = "FAIL";
//    char string4[15] = "no change";
//    char string5[15] = "Linked";
//    char string6[15] = "Unlink";
//    unsigned const char responses[6] = {ESP8266_OK, ESP8266_READY, ESP8266_FAIL, ESP8266_NOCHANGE, ESP8266_LINKED, ESP8266_UNLINK};
//    unsigned char received;
//    unsigned char response;
//    bool continue_loop = true;
//    while (continue_loop) {
//        received = esp8266_getch();
//        for (unsigned char i = 0; i < 6; i++) {
//            if (strings[i][so_far[i]] == received) {
//                so_far[i]++;
//                if (so_far[i] == lengths[i]) {
//                    response = responses[i];
//                    continue_loop = false;
//                }
//            } else {
//                so_far[i] = 0;
//            }
//        }
//    }
//    return response;
//}
