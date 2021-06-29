#include "stc8.h"
#include "uart.h"
/**********************************************************
*���ڲ��ִ���
***********************************************************/
extern unsigned char tmp2;
extern unsigned char mudi;
extern unsigned char ss;
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

void uart2_send(ss)
{
   	ES= 0;

   	   
  //��������
  S2BUF=ss;						//����0x0a
  while(S2CON&S2TI==0);				// �������ݴ���	(S2TI�����жϱ�־)
  S2CON&=~S2TI;						//���־λ
	  
    }   


void uart2_receive() interrupt 8
{
  if(S2CON&S2RI)						//����յ����� S2RI��λ
  {
   tmp2=S2BUF;	
   S2CON&=~S2RI;						//���־λ  
  }
}



