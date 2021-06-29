#include "stc8.h"
#include "uart.h"
/**********************************************************
*串口部分处理
***********************************************************/
extern unsigned char tmp2;
extern unsigned char mudi;
extern unsigned char ss;
#define FOSC 27000000L			  //MUC主频为27mhz下
#define BAUD 9600				  //串口2产生的波特率为9600
#define TM  (65536-(FOSC/4/BAUD)) //计算初值

//串口2
//串口2初始化操作 
void uart2_init() 
 {

 S2CON = 0x50;       //REN=1允许串行接受状态，串口工作模式2     	                 
  T2L=TM;			  //配置串口2波特率	 初始值
  T2H=TM>>8;                    
  AUXR=0X14;		  //开启定时器T2  并且开启1T模式
  IE2=0X01;           //串口2中断使能                                                           
  EA   = 1;           // 开总中断 
}

void uart2_send(ss)
{
   	ES= 0;

   	   
  //发送数据
  S2BUF=ss;						//发送0x0a
  while(S2CON&S2TI==0);				// 等特数据传送	(S2TI发送中断标志)
  S2CON&=~S2TI;						//清标志位
	  
    }   


void uart2_receive() interrupt 8
{
  if(S2CON&S2RI)						//如果收到数据 S2RI置位
  {
   tmp2=S2BUF;	
   S2CON&=~S2RI;						//清标志位  
  }
}



