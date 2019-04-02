#include <xc.h>
#include <stdbool.h>

//Bluetooth properties

#define MAX 15
#define STR_LEN 100

typedef struct
{
    int packetIndex;
    int packetSize;
    int count;
    char foundBT[MAX][STR_LEN]; // 10 strings of 100 length
    char packetBuf[1024];
    bool packetEOT;
    bool isConnected;
} BLE_DATA;

extern BLE_DATA bleData;

void BLE_connect(int);
void BLE_parseT1(char[]);