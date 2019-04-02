#include <xc.h>
#include <stdbool.h>

//Bluetooth properties
typedef struct
{
    int packetIndex;
    int packetSize;
    int count;
    //char* pstr[10];
    char packetBuf[1024];
    bool packetEOT;
} BLE_DATA;

extern BLE_DATA bleData;

void BLE_connect(int);
char* BLE_parse(char[]);
char* BLE_parseT1(char[]);