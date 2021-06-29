 /****************************************
*传感器模块
****************************************/

#include "stc8.h"
#include "moto.h"
#include "delay.h"
#include "searchline.h"
#define qian1 P14
#define qian2 P15
#define qian3 P13
#define zuo1 P54
#define zuo2 P55
#define zuo3 P12
#define you1 P53
#define you2 P01
#define you3 P00
#define hou1 P50
#define hou2 P52
#define hou3 P51

//传感器位置判断
#define yaxian 1                      //注意:1为压线,0为未压线
#define weiyaxian 0
#define yanshi 1                      //延时数值
extern int stop1,stop2,stop3,stop4;
extern int pwm1,pwm2,pwm3,pwm4;



int linec()
{
if (you2==yaxian && hou2==weiyaxian && zuo2==weiyaxian && hou1==weiyaxian && hou3==weiyaxian)
return 1;
else
return 0;
}

int lineb()
{
if (you2==yaxian && qian2==yaxian && zuo2==yaxian && hou2==yaxian)
return 1;
else
return 0;
}

int linea()
{
if (you2==yaxian && hou2==yaxian&&zuo2==weiyaxian&&qian2==weiyaxian&&qian1==weiyaxian&&qian3==weiyaxian)
return 1;
else
return 0;
}

int lined()
{
if (you2==yaxian)
return 1;
else
return 0;
}

int linee()
{
if (hou2==weiyaxian && hou1==weiyaxian && hou3==weiyaxian)
return 1;
else
return 0;
}



//横向修正基准
void hengzuo()        //左平移时
{
	zuopingyi();
if(you1==yaxian && you2==weiyaxian)
{
tingzhi1();
tingzhi2();
}
if(you3==yaxian && you2==weiyaxian)
{ 
tingzhi3();
tingzhi4();
}
if(zuo1==yaxian && zuo2==weiyaxian)
{
tingzhi3();
tingzhi4();
}
if(zuo3==yaxian && zuo2==weiyaxian)
{
tingzhi1();
tingzhi2();
}
if(you1==yaxian && zuo1==yaxian)
{
qianjin();
}
if(you3==yaxian && zuo3==yaxian)
{
houtui();

}
}
void hengyou()        //右平移时
{
youpingyi();
if(you1==yaxian && you2==weiyaxian)
{
tingzhi3();
tingzhi4();
}
if(you3==yaxian && you2==weiyaxian)
{ 
tingzhi1();
tingzhi2();
}
if(zuo1==yaxian && zuo2==weiyaxian)
{
tingzhi1();
tingzhi2();
}
if(zuo3==yaxian && zuo2==weiyaxian)
{
tingzhi3();
tingzhi4();
}
if(you1==yaxian && zuo1==yaxian)
{
qianjin();
}
if(you3==yaxian && zuo3==yaxian)
{
houtui();
}
}
//纵向修正基准
void zongqian()
{
qianjin();

if(hou1==yaxian&&hou2==weiyaxian)
	tingzhi3();
if(hou3==yaxian&&hou2==weiyaxian)
  tingzhi4();

if(qian1==yaxian && qian2==weiyaxian)
{
	tingzhi1();
}
if(qian3==yaxian && qian2==weiyaxian)
{
	tingzhi2();
}
if(qian1==yaxian&&hou1==yaxian)
	zuopingyi();
if(qian3==yaxian&&hou3==yaxian)
	youpingyi();
}

void zonghou()
{
houtui();

if(hou1==yaxian&&hou2==weiyaxian)
	tingzhi3();
if(hou3==yaxian&&hou2==weiyaxian)
  tingzhi4();

if(qian1==yaxian && qian2==weiyaxian)
{
	tingzhi1();
}
if(qian3==yaxian && qian2==weiyaxian)
{
	tingzhi2();
}
if(qian1==yaxian&&hou1==yaxian)
	zuopingyi();
if(qian3==yaxian&&hou3==yaxian)
	youpingyi();
}
