#include "STC8.h"
#include "intrins.h"
#include "io.h"
#include "delay.h"
#include "moto.h"
#include "searchline.h"
#include "uart.h"
//int finish=0;
unsigned char ss;
unsigned char tmp1;
unsigned char tmp2;
unsigned char mudi;   //接收acs2编码,接收目标值
unsigned char address;  //当前位置的acs2编码
int finish1,finish2,finish3,finish4;
int stop1=7,stop2=7,stop3=7,stop4=7;

int dongzuo=0;   //1为前进。。。。。。。。。
//int mudi=0;      //目的变量
int finish=0;
int finish1=0;
int pwm1=0,pwm2=0,pwm3=0,pwm4=0;
int p6;
int p4;



/*主函数入口*/
void main()
  { P06=0;
		P04=0;
		io_init();                //io初始化
//		mudi='D';
	 	uart2_init();             //串口2初始
	/*  time1_init();             //硬件定时器初始化
	  	time2_init();
	  	time3_init();
	  	time4_init();*/
		address='E';
		finish=0;
		while(1)
	{
	//	address='E';		
		
	//	mudi='D';
		if(mudi=='R'&&address!='E')
	  {	
			address='E';
	 uart2_send('R');	
   delay_ms(10);	 
	 uart2_send('\n');
	 delay_ms(10);	}
 //  mudi=tmp2;	
		//A节点处理
		if(address=='A')
		{
	   if(mudi=='B')
		 {
		   zonghou(); 
		 if(P55==1)
		 { address='B';
			 tingzhi();
			 uart2_send('B');
			  delay_ms(10);	
		 uart2_send('\n');
		  delay_ms(10);	}
		 }
	  }
		//B节点处理
		if(address=='B')
		{
	    if(mudi=='C')
		 {
		   zonghou(); 
			 delay_ms(150);
		 if(linec()==1)
		 { address='C';
			 tingzhi();
			 uart2_send('C');
			  delay_ms(10);	
		 uart2_send('\n');
		  delay_ms(10);	}
		 }
		 if(mudi=='A')
		 {
		   zongqian(); 
			 delay_ms(150);
		 if(linea()==1)
		 {address='A';
			 tingzhi();
			 uart2_send('A');
			  delay_ms(10);	
		 uart2_send('\n');
		  delay_ms(10);	}
		 }
		 if(mudi=='D')
		 {
		   hengzuo(); 
			 delay_ms(150);
		 if(lined()==1)
		 { address='D';
			 tingzhi();
			 uart2_send('D');
			  delay_ms(10);	
		 uart2_send('\n');
		  delay_ms(10);	}
		 }
	  }
		//C节点处理
    if(address=='C')
		{
	   if(mudi=='B')
		 {
		   zongqian(); 
			 delay_ms(150);
		 if(P15==1)
		 {address='B';
			 tingzhi();
			 uart2_send('B');
			  delay_ms(10);	
		 uart2_send('\n');
		  delay_ms(10);	}
		 }
	  }
		//D节点处理
    if(address=='D')
		{
	    if(mudi=='B')
		 {
		   hengyou(); 
			  delay_ms(150);
		 if(P01==1)
		 {address='B';
			 tingzhi();
			 uart2_send('B');
			  delay_ms(10);	
		 uart2_send('\n');
		  delay_ms(10);	}
		 }
		 if(mudi=='E')
		 {
		   zonghou(); 
			  delay_ms(150);
		 if(linee()==1)
		 {address='E';
			 tingzhi();
			 uart2_send('E');
			  delay_ms(10);	
		 uart2_send('\n');
		  delay_ms(10);	}
		 }
	  }
		//E节点处理
    if(address=='E')			
		{
	   if(mudi=='D')
		 { 
			 zongqian();
			 delay_ms(150);
}
			 
		
		 if(lined()==1)
		 { 
       address='D';
			 tingzhi();
			 uart2_send('D');
			 delay_ms(10);	
		 uart2_send('\n');
		 delay_ms(10);	
		}

		 }
if(P06==1)
{address='E';
	mudi='D';}
if(P04==1)
{address='D';
	mudi='E';}
if (finish==0)
{
	delay_ms(5000);
	address='E';
	mudi='D';
	finish=1;
	}
		
	}	}
