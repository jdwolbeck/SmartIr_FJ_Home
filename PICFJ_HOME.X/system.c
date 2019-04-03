#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdlib.h>
#include "system.h"

void delay(int ms)
{
    int i,j;
    for(i = 2*ms; i > 0; i--)
    {
        for(j = 284; j > 0; j--);
    }
    j = 0;
}

char* charToString(char ch)
{
    // malloc allocates space for 2 characters in memory and returns a character pointer
    char *str = (char*)malloc(2*sizeof(char));
    str[0] = ch;
    str[1] = '\0';
    return str; 
}