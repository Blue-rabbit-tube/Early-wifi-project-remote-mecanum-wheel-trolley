#include "stc8.h"
#include "intrins.h"

#define FOSC            27000000L
#define BRT             (65536 - FOSC / 115200 / 4)       //?????????????????????interesting


bit busys;
char wptr;
char rptr;
char buffer[16];
extern char servosend[5];

void UartIsr() interrupt 4
{
    if (TI)
    {
        TI = 0;
        busys = 0;
    }
    if (RI)
    {
        RI = 0;
        buffer[wptr++] = SBUF;
        wptr &= 0x0f;
    }
}

void UartInit()
{
    SCON = 0x50;
    TMOD = 0x00;
    TL1 = BRT;
    TH1 = BRT >> 8;
    TR1 = 1;
    AUXR = 0x40;
    wptr = 0x00;
    rptr = 0x00;
    busys = 0;
	  ES = 1;
}

void UartSend(char dat)
{
    while (busys);
    busys = 1;
    SBUF = dat;
}

void uart1_printf(char *p)
{
    while (*p)
    {
        UartSend(*p++);
    }
}

void uart1_init()
{
    UartInit();
}

void uart2_send(char dat)
{
    while (busys);
    busys = 1;
    SBUF = dat;
}


