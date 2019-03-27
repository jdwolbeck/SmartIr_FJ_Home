#include <xc.h>
#include <stdbool.h>

//Bluetooth properties
typedef struct
{
    int packetIndex;
    int packetSize;
    char packetBuf[40];
    bool packetEOT;
} BLE_DATA;

extern BLE_DATA bleData;

void BLE_connect(void);