#include "STC8.H"
#include "intrins.h"

unsigned char tmp1;
unsigned char tmp2;


/**********************************************************
*ȫ�������ʱ���ִ���
***********************************************************/

//΢�뼶����ʱ
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

//���뼶����ʱ
int delay_ms(int c)
{
for (;c<=1;c--)
{
delay_us(1000);
}
				return 0;
}



/**********************************************************
*���ڲ��ִ���
***********************************************************/

#define FOSC 27000000L			  //MUC��ƵΪ27mhz��
#define BAUD 9600				  //����2�����Ĳ�����Ϊ9600
#define TM  (65536-(FOSC/4/BAUD)) //�����ֵ

//����2
//����2��ʼ������ 


void uart2_init() 
 {

 S2CON = 0x50;       //REN=1�����н���״̬�����ڹ���ģʽ2     	                 
  T2L=TM;			  //���ô���2������	 ��ʼֵ
  T2H=TM>>8;                    
  AUXR=0X14;		  //������ʱ��T2  ���ҿ���1Tģʽ
  IE2=0X01;           //����2�ж�ʹ��                                                           
  EA   = 1;           // �����ж� 
}

void uart2_send()
{
   	ES= 0;

   	   
  //��������
  S2BUF=0x33;						//����0x0a
  while(S2CON&S2TI==0);				// �������ݴ���	(S2TI�����жϱ�־)
  S2CON&=~S2TI;						//���־λ
	   
     

    }   


void uart2_receive() interrupt 8 using 2
{
  if(S2CON&S2RI)						//����յ����� S2RI��λ
  {
   tmp2= S2BUF;	
   S2CON&=~S2RI;						//���־λ  
  }
}


/*���������*/
void main()
  { 
		int dongzuo;
		int jingdongzhi;
		int finish;
		uart2_init();             //����2��ʼ��
		tmp2=0x00;
		jingdongzhi=0x00;
		finish=0;
		while(1)
		{

		dongzuo=(tmp2/(0x10));		      //���ڽ��յ����ݴ���(�������ݻ��Զ����ǣ����ù�tmp1����ֵ��
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

//���װ棬�ȶ�����