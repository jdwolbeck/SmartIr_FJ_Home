#include <xc.h>
#include <stdbool.h>

//Bluetooth properties

#define MAX 15
#define NUM_OF_SENSORS 3
#define STR_LEN 500

typedef struct
{
    bool en;
    int packetIndex;
    int packetSize;
    int count;
    char foundBT[MAX][STR_LEN]; // 10 strings of 100 length
    char sensors[NUM_OF_SENSORS][STR_LEN];
    char packetBuf[1024];
    bool packetEOT;
    bool isConnected;
    bool streamConn;
} BLE_DATA;

extern BLE_DATA bleData;

void BLE_connect(int);
void BLE_parseT1(char[]);
void BLE_searchStream(char[]);