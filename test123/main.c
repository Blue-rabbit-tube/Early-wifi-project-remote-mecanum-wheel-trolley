/*
作者：姜卓谞
*/

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

//串口1初始化
void uart1_init() 
{



        SCON = 0x50;       //REN=1允许串行接受状态，串口工作模式2     	   
	    TMOD= 0x20;      //定时器工作方式2       8位 自动重装载定时器  实现波特率                

	   AUXR=0X40;		 //开启1T模式


	   TH1 =TL1= 0xA9;			//  设置波特率为9600  公式 TH1=256-(27000000/32/9600)=256-87=169  0xA9

		TR1  = 1;        //开启定时器1                                                                      
		EA   = 1;        // 开总中断 

}

void uart1_send()
{
char  code  MESSAGE[]= "我爱单片机 ";
	
  unsigned char a;

	  a=0;
	   while(MESSAGE[a]!= '\0')
   	   {
		SBUF = MESSAGE[a];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
         while(!TI);				// 等特数据传送	(TI发送中断标志)
		 TI = 0;					// 清除数据传送标志
		
		a++;					    // 下一个字符
       } 
 delay_us(1);
    }   



void uart1_receive() interrupt 4 using 1
{ 
	if (RI) 
    {
//接收数据
      tmp1 = SBUF;
      RI = 0;
    }
}  

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



//编码器pid闭环控制的看不懂函数（应该是自动化控制原理里的闭环控制公式）（希望大佬进行技术支持）
//可能要进行参数调节优化，返回的目测不是一个整型数字
//此处为整个程序的核心算法


int Position_PID (int Encoder,int Target)                //需要给出编码值和目标值
{ 
	/* float Position_KP=80,Position_KI=0.1,Position_KD=500;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
	 */
	   int cesuanzhi;
		 cesuanzhi=Target-Encoder;
		 return cesuanzhi;
}


//读取编码器计数
int jishu1;
int jishu2;
int jishu3;
int jishu4;

void jishu_init() //100毫秒中断
{
T4T3M |= 0x02;		
	T3L = 0xF2;		
	T3H = 0xFE;	
	T4T3M |= 0x08;	
	IE2=ET3;
	EA=1; 	
}

int Read_Encoder() interrupt 19
{
       
   if (P21==1 )		 //各种计数器接口（暂时只使用单计数器计数）（双计数器在摸索ing）
     jishu1++;
	 if (P23==1 )
		 jishu2++;
	 if (P25==1 )
		 jishu3++;
	 if (P27==1 )
		 jishu4++;
}


//绝对值函数

int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

//限制pid数值

int paolu;
int mubiaozhi1;
int mubiaozhi2;
int mubiaozhi3;
int mubiaozhi4;


void Xianfu_Pwm()
{	  
	  int paolu=5;    //定义最大允许的偏差范围,调参警告
    if((myabs(jishu1)-myabs(mubiaozhi1))<paolu) jishu1=mubiaozhi1;	
		if((myabs(jishu2)-myabs(mubiaozhi2))<paolu) jishu2=mubiaozhi2;
		if((myabs(jishu3)-myabs(mubiaozhi3))<paolu) jishu3=mubiaozhi3;
	  if((myabs(jishu4)-myabs(mubiaozhi4))<paolu) jishu4=mubiaozhi4;
}

//赋值给pwm
/************************
      重点
************************/

int motol1;
int motol2;
int motol3;
int motol4;

void Set_Pwm()
{
			if(motol1>0)		            	P32=1,			P33=0;       //没到目标值，继续前进，并配置io口 暂未配置某个io口
 			else if(motol1<0) 	          P32=0,			P33=1;       //过了目标值，倒退，并配置io口 暂未配置某个io口
			else                          P32=0,      P33=0;                   //原地不动
			delay_us(5);
			if(motol2>0)		            	P34=0,			P35=1;       //没到目标值，继续前进，并配置io口 暂未配置某个io口
 			else if(motol2<0) 	          P34=1,			P35=0;       //过了目标值，倒退，并配置io口 暂未配置某个io口
			else                          P34=0,      P35=0;                   //原地不动
			delay_us(5);
			if(motol3>0)		            	P36=1,			P37=0;       //没到目标值，继续前进，并配置io口 暂未配置某个io口
 			else if(motol3<0) 	          P36=0,			P37=1;       //过了目标值，倒退，并配置io口 暂未配置某个io口
			else                          P36=0,      P37=0;                   //原地不动
			delay_us(5);
			if(motol4>0)		            	P41=1,			P42=0;       //没到目标值，继续前进，并配置io口 暂未配置某个io口
 			else if(motol4<0) 	          P41=0,			P42=1;       //过了目标值，倒退，并配置io口 暂未配置某个io口
			else                          P41=0,      P42=0;                   //原地不动
			delay_us(5);
						
}

//两个时钟(暂时没用)



//pwm控制部分
/************************
重点
************************/




void pwm_control()                   //调参位置
{     
			do
			{
		  motol1=Position_PID(jishu1,mubiaozhi1);              
			motol2=Position_PID(jishu2,mubiaozhi2);              
			motol3=Position_PID(jishu3,mubiaozhi3);             
			motol4=Position_PID(jishu4,mubiaozhi4);             
		  Xianfu_Pwm();              	
    	Set_Pwm();            			
			}
			while (((motol1+motol2+motol3+motol4)-(mubiaozhi1+mubiaozhi2+mubiaozhi3+mubiaozhi4))==0);

}


/*主函数入口*/
void main()
  { int dongzuo;
		int jingdongzhi;
		int finish;
	  uart1_init();             //串口1初始化
		uart2_init();             //串口2初始化
		tmp2=0x00;
		while(1)
		{

	//	dongzuo=tmp2/0xa;		      //串口接收的数据处理(有新数据会自动覆盖，不用管tmp1的数值）
  //	jingdongzhi=(tmp2-(dongzuo*10))*50;
	  jingdongzhi=50;
	if (tmp2==0x11)
	{mubiaozhi1=jingdongzhi;
		mubiaozhi2=jingdongzhi;
		mubiaozhi3=jingdongzhi;
		mubiaozhi4=jingdongzhi;
		pwm_control();
		jishu_init(); 
		finish=1;
		}
 else if (tmp2==0x22)
	{mubiaozhi1=-jingdongzhi;
		mubiaozhi2=-jingdongzhi;
		mubiaozhi3=-jingdongzhi;
		mubiaozhi4=-jingdongzhi;
		pwm_control();
		jishu_init(); 
		finish=1;
	}
 else if (tmp2==0x33)
	{mubiaozhi1=jingdongzhi;
		mubiaozhi2=-jingdongzhi;
		mubiaozhi3=jingdongzhi;
		mubiaozhi4=-jingdongzhi;
		pwm_control();
		jishu_init(); 
		finish=1;
	}
 else if (tmp2==0x44)
	{	mubiaozhi1=-jingdongzhi;
		mubiaozhi2=jingdongzhi;
		mubiaozhi3=-jingdongzhi;
		mubiaozhi4=jingdongzhi;
		pwm_control();
		jishu_init(); 
		finish=1;
		}
	tmp2=0x00;
	if(finish==1)
	uart2_send();
	finish=0;
}
}

	
	
	
//确实佩服轮子设计者以及程序书写者的智慧