#include "stc8.h"
#include "moto.h"
#include "delay.h"
void zuopingyi()
{
delay_ms(1500);
P44=~P44;
P34=~P34;
P36=~P36;
P37=~P37;
P17=0;
P16=0;
P41=1;
P42=1;
}
void youpingyi()
{
delay_ms(1500);
P44=~P44;
P34=~P34;
P36=~P36;
P37=~P37;
P17=1;      //P17 high 2�ŵ����ת
P16=1;      //P16 high 1�ŵ����ת
P41=0;      //P41 low 3�ŵ����ת
P42=0;      //P42 high 4�ŵ����ת
}
void houtui()
{
delay_ms(1500);
P44=~P44;
P34=~P34;
P36=~P36;
P37=~P37;
P17=1;
P16=0;
P41=0;
P42=1;
}
void qianjin()
{
delay_ms(1500);
P44=~P44;
P34=~P34;
P36=~P36;
P37=~P37;
P17=0;
P16=1;
P41=1;
P42=0;
}

void tingzhi2()
{
P34=0;
}
void tingzhi1()
{
P44=0;
}
void tingzhi4()
{
P36=0;
}
void tingzhi3()
{
P37=0;
}
void tingzhi()
{
P44=0;
P34=0;
P36=0;
P37=0;
}


