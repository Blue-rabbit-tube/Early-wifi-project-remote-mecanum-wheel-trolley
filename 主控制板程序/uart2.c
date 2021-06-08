//uart2 using timer2

#include "stc8.h"
#include "intrins.h"
#include "uart2.h"

extern char uart2buf[50];
extern int uart2datacount=0;
typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 27000000L          //系统频率
#define BAUD 115200             //串口波特率

#define NONE_PARITY     0       //无校验
#define ODD_PARITY      1       //奇校验
#define EVEN_PARITY     2       //偶校验
#define MARK_PARITY     3       //标记校验
#define SPACE_PARITY    4       //空白校验

#define PARITYBIT NONE_PARITY   //定义校验位
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
    S2CON = 0x50;               //8位可变波特率
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S2CON = 0xda;               //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
    S2CON = 0xd2;               //9位可变波特率,校验位初始为0
#endif

    T2L = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    IE2 = 0x01;                 //使能串口2中断
    EA = 1;
}

/*----------------------------
UART2 中断服务程序
-----------------------------*/
void uart2_receive() interrupt 8
{
	char bittest1;
	char bittest2;
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;         //清除S2RI位
			
        bittest1 = S2BUF;             //P0显示串口数据
			if(bittest1!='\n')
			{
			uart2buf[uart2datacount]=bittest1;
				uart2datacount++;
			}
				else
				{
				uart2datacount=0;
				}
        				
        bittest2 = (S2CON & S2RB8);   //P2.2显示校验位
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;         //清除S2TI位
        busy = 0;               //清忙标志
    }
}

/*----------------------------
发送串口数据
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);               //等待前面的数据发送完成
    ACC = dat;                  //获取校验位P (PSW.0)
    if (P)                      //根据P来设置校验位
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON &= ~S2TB8;        //设置校验位为0
#elif (PARITYBIT == EVEN_PARITY)
        S2CON |= S2TB8;         //设置校验位为1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON |= S2TB8;         //设置校验位为1
#elif (PARITYBIT == EVEN_PARITY)
        S2CON &= ~S2TB8;        //设置校验位为0
#endif
    }
    busy = 1;
    S2BUF = ACC;                //写数据到UART2数据寄存器
}

/*----------------------------
发送字符串
----------------------------*/
void uart2_printf(char *s)
{
    while (*s)                  //检测字符串结束标志
    {
        SendData(*s++);         //发送当前字符
    }
}

