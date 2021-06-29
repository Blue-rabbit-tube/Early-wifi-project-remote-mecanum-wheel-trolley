/*
���ߣ���׿נ
*/

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

//����1��ʼ��
void uart1_init() 
{



        SCON = 0x50;       //REN=1�����н���״̬�����ڹ���ģʽ2     	   
	    TMOD= 0x20;      //��ʱ��������ʽ2       8λ �Զ���װ�ض�ʱ��  ʵ�ֲ�����                

	   AUXR=0X40;		 //����1Tģʽ


	   TH1 =TL1= 0xA9;			//  ���ò�����Ϊ9600  ��ʽ TH1=256-(27000000/32/9600)=256-87=169  0xA9

		TR1  = 1;        //������ʱ��1                                                                      
		EA   = 1;        // �����ж� 

}

void uart1_send()
{
char  code  MESSAGE[]= "�Ұ���Ƭ�� ";
	
  unsigned char a;

	  a=0;
	   while(MESSAGE[a]!= '\0')
   	   {
		SBUF = MESSAGE[a];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
         while(!TI);				// �������ݴ���	(TI�����жϱ�־)
		 TI = 0;					// ������ݴ��ͱ�־
		
		a++;					    // ��һ���ַ�
       } 
 delay_us(1);
    }   



void uart1_receive() interrupt 4 using 1
{ 
	if (RI) 
    {
//��������
      tmp1 = SBUF;
      RI = 0;
    }
}  

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



//������pid�ջ����ƵĿ�����������Ӧ�����Զ�������ԭ����ıջ����ƹ�ʽ����ϣ�����н��м���֧�֣�
//����Ҫ���в��������Ż������ص�Ŀ�ⲻ��һ����������
//�˴�Ϊ��������ĺ����㷨


int Position_PID (int Encoder,int Target)                //��Ҫ��������ֵ��Ŀ��ֵ
{ 
	/* float Position_KP=80,Position_KI=0.1,Position_KD=500;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //�������
	 */
	   int cesuanzhi;
		 cesuanzhi=Target-Encoder;
		 return cesuanzhi;
}


//��ȡ����������
int jishu1;
int jishu2;
int jishu3;
int jishu4;

void jishu_init() //100�����ж�
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
       
   if (P21==1 )		 //���ּ������ӿڣ���ʱֻʹ�õ���������������˫������������ing��
     jishu1++;
	 if (P23==1 )
		 jishu2++;
	 if (P25==1 )
		 jishu3++;
	 if (P27==1 )
		 jishu4++;
}


//����ֵ����

int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

//����pid��ֵ

int paolu;
int mubiaozhi1;
int mubiaozhi2;
int mubiaozhi3;
int mubiaozhi4;


void Xianfu_Pwm()
{	  
	  int paolu=5;    //������������ƫ�Χ,���ξ���
    if((myabs(jishu1)-myabs(mubiaozhi1))<paolu) jishu1=mubiaozhi1;	
		if((myabs(jishu2)-myabs(mubiaozhi2))<paolu) jishu2=mubiaozhi2;
		if((myabs(jishu3)-myabs(mubiaozhi3))<paolu) jishu3=mubiaozhi3;
	  if((myabs(jishu4)-myabs(mubiaozhi4))<paolu) jishu4=mubiaozhi4;
}

//��ֵ��pwm
/************************
      �ص�
************************/

int motol1;
int motol2;
int motol3;
int motol4;

void Set_Pwm()
{
			if(motol1>0)		            	P32=1,			P33=0;       //û��Ŀ��ֵ������ǰ����������io�� ��δ����ĳ��io��
 			else if(motol1<0) 	          P32=0,			P33=1;       //����Ŀ��ֵ�����ˣ�������io�� ��δ����ĳ��io��
			else                          P32=0,      P33=0;                   //ԭ�ز���
			delay_us(5);
			if(motol2>0)		            	P34=0,			P35=1;       //û��Ŀ��ֵ������ǰ����������io�� ��δ����ĳ��io��
 			else if(motol2<0) 	          P34=1,			P35=0;       //����Ŀ��ֵ�����ˣ�������io�� ��δ����ĳ��io��
			else                          P34=0,      P35=0;                   //ԭ�ز���
			delay_us(5);
			if(motol3>0)		            	P36=1,			P37=0;       //û��Ŀ��ֵ������ǰ����������io�� ��δ����ĳ��io��
 			else if(motol3<0) 	          P36=0,			P37=1;       //����Ŀ��ֵ�����ˣ�������io�� ��δ����ĳ��io��
			else                          P36=0,      P37=0;                   //ԭ�ز���
			delay_us(5);
			if(motol4>0)		            	P41=1,			P42=0;       //û��Ŀ��ֵ������ǰ����������io�� ��δ����ĳ��io��
 			else if(motol4<0) 	          P41=0,			P42=1;       //����Ŀ��ֵ�����ˣ�������io�� ��δ����ĳ��io��
			else                          P41=0,      P42=0;                   //ԭ�ز���
			delay_us(5);
						
}

//����ʱ��(��ʱû��)



//pwm���Ʋ���
/************************
�ص�
************************/




void pwm_control()                   //����λ��
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


/*���������*/
void main()
  { int dongzuo;
		int jingdongzhi;
		int finish;
	  uart1_init();             //����1��ʼ��
		uart2_init();             //����2��ʼ��
		tmp2=0x00;
		while(1)
		{

	//	dongzuo=tmp2/0xa;		      //���ڽ��յ����ݴ���(�������ݻ��Զ����ǣ����ù�tmp1����ֵ��
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

	
	
	
//ȷʵ�������������Լ�������д�ߵ��ǻ�