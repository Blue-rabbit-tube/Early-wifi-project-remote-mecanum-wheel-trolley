//uart2 using timer2

#include "stc8.h"
#include "intrins.h"
#include "uart2.h"

extern char uart2buf[50];
extern int uart2datacount=0;
typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 27000000L          //ϵͳƵ��
#define BAUD 115200             //���ڲ�����

#define NONE_PARITY     0       //��У��
#define ODD_PARITY      1       //��У��
#define EVEN_PARITY     2       //żУ��
#define MARK_PARITY     3       //���У��
#define SPACE_PARITY    4       //�հ�У��

#define PARITYBIT NONE_PARITY   //����У��λ
#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3
#define S2_S0 0x01              //P_SW2.0

bit busy;

void uart2_init()
{
    P_SW2 &= ~S2_S0;            //S2_S0=0 (P1.0/RxD2, P1.1/TxD2)

#if (PARITYBIT == NONE_PARITY)
    S2CON = 0x50;               //8λ�ɱ䲨����
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S2CON = 0xda;               //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (PARITYBIT == SPACE_PARITY)
    S2CON = 0xd2;               //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif

    T2L = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
    IE2 = 0x01;                 //ʹ�ܴ���2�ж�
    EA = 1;
}

/*----------------------------
UART2 �жϷ������
-----------------------------*/
void uart2_receive() interrupt 8
{
	char bittest1;
	char bittest2;
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;         //���S2RIλ
			
        bittest1 = S2BUF;             //P0��ʾ��������
			if(bittest1!='\n')
			{
			uart2buf[uart2datacount]=bittest1;
				uart2datacount++;
			}
				else
				{
				uart2datacount=0;
				}
        				
        bittest2 = (S2CON & S2RB8);   //P2.2��ʾУ��λ
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;         //���S2TIλ
        busy = 0;               //��æ��־
    }
}

/*----------------------------
���ʹ�������
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);               //�ȴ�ǰ������ݷ������
    ACC = dat;                  //��ȡУ��λP (PSW.0)
    if (P)                      //����P������У��λ
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON &= ~S2TB8;        //����У��λΪ0
#elif (PARITYBIT == EVEN_PARITY)
        S2CON |= S2TB8;         //����У��λΪ1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON |= S2TB8;         //����У��λΪ1
#elif (PARITYBIT == EVEN_PARITY)
        S2CON &= ~S2TB8;        //����У��λΪ0
#endif
    }
    busy = 1;
    S2BUF = ACC;                //д���ݵ�UART2���ݼĴ���
}

/*----------------------------
�����ַ���
----------------------------*/
void uart2_printf(char *s)
{
    while (*s)                  //����ַ���������־
    {
        SendData(*s++);         //���͵�ǰ�ַ�
    }
}

