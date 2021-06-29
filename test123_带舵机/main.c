#include "STC8.H"
#include "intrins.h"

unsigned char tmp1;
unsigned char tmp2;


/**********************************************************
*全局软件延时部分处理
***********************************************************/

//微秒级别延时
int delay_us(int d)
{
for (;d<=1;d--)
{
	 unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=3;a>0;a--);

}
				return 0;
}

//毫秒级别延时
int delay_ms(int c)
{
for (;c<=1;c--)
{
delay_us(1000);
}
				return 0;
}



/**********************************************************
*串口部分处理
***********************************************************/

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

void uart2_send()
{
   	ES= 0;

   	   
  //发送数据
  S2BUF=0x33;						//发送0x0a
  while(S2CON&S2TI==0);				// 等特数据传送	(S2TI发送中断标志)
  S2CON&=~S2TI;						//清标志位
	   
     

    }   


void uart2_receive() interrupt 8 using 2
{
  if(S2CON&S2RI)						//如果收到数据 S2RI置位
  {
   tmp2= S2BUF;	
   S2CON&=~S2RI;						//清标志位  
  }
}


/*主函数入口*/
void main()
  { 
		int dongzuo;
		int jingdongzhi;
		int finish;
		uart2_init();             //串口2初始化
		tmp2=0x00;
		jingdongzhi=0x00;
		finish=0;
		while(1)
		{

		dongzuo=(tmp2/(0x10));		      //串口接收的数据处理(有新数据会自动覆盖，不用管tmp1的数值）
  	jingdongzhi=((tmp2%(0x10))*(0x2000000));
	if (dongzuo==3)
	{
		P32=1,P33=0;
		P34=1,P35=0;
		P36=1,P37=0;  
		P41=1,P42=0; 
		delay_ms(jingdongzhi);
		P32=0,P33=0;
		P34=0,P35=0;
		P36=0,P37=0;  
		P41=0,P42=0; 
		finish=1;
		}
 else if (dongzuo==4)
	{
		P32=0,P33=1;
		P34=0,P35=1;
		P36=0,P37=1;  
		P41=0,P42=1; 
		delay_ms(jingdongzhi);
		P32=0,P33=0;
		P34=0,P35=0;
		P36=0,P37=0;  
		P41=0,P42=0; 
		finish=1;
	}
 else if (dongzuo==2)
	{ 
		P32=1,P33=0;
		P34=0,P35=1;
		P36=1,P37=0;  
		P41=0,P42=1; 
		delay_ms(jingdongzhi);
		P32=0,P33=0;
		P34=0,P35=0;
		P36=0,P37=0;  
		P41=0,P42=0; 
		finish=1;
	}
 else if (dongzuo==1)
	{
		P32=0,P33=1;
		P34=1,P35=0;
		P36=0,P37=1;  
		P41=1,P42=0; 
		delay_ms(jingdongzhi);
		P32=0,P33=0;
		P34=0,P35=0;
		P36=0,P37=0;  
		P41=0,P42=0; 
		finish=1;
		}
	
	if(finish==1)
	{uart2_send();
	 tmp2=0x00;
	 jingdongzhi=0x00;
		}
	 finish=0;
}
}

//简易版，稳定可用