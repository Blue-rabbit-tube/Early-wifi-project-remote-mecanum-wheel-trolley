#include "stc8.h"
#include "delay.h"
#include "intrins.h"
/**********************************************************
*ȫ�������ʱ���ִ���
***********************************************************/
/*
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
*/
//���뼶����ʱ
int delay_ms(int c)
{
	for(;c>=0;c--)
{			unsigned char i;

	i = 7;
	while (--i);
};
return 0;}


/**********************************************************
*Ӳ����ʱ����ʼ��
***********************************************************/
/*
void time1_init()
{
TMOD=0x44;
TL0=0xfa;
TH0=0xff;
TR0=1;
ET0=1;
EA=1;
}
void time2_init()
{
//TMOD=0x44;
TL1=0xfa;
TH1=0xff;
TR1=1;
ET1=1;
EA=1;
}
void time3_init()
{
T3L=0xfa;
T3H=0xff;
T4T3M=0xcc;                   //��ѧ�������������Ĵ���ֻ�ܶ���һ��
IE2=0x61;
EA=1;
}
void time4_init()
{
T4L=0xfa;
T4H=0xff;
//T4T3M=0xc9;
//IE2=ET4;
EA=1;
}
*/
