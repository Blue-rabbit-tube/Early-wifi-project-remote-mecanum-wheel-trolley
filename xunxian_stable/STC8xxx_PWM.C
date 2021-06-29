
#include "config.h"
#include "STC8xxx_PWM.H"


void PWMGO(void)
{
//	int i=1;

	//设置需要使用的PWM输出口为强推挽模式
	P20 = 0;
	P21 = 0;
	P22 = 0;
	P23 = 0;
//	P24 = 0;
//	P25 = 0;
//	P26 = 0;
//	P27 = 0;
	P2n_push_pull(0x0f);	// PWM0-P2.0	PWM1-P2.1  PWM2-P2.2  PWM3-P2.3	PWM4-P2.4	PWM5-P2.5  PWM6-P1.6  PWM7-P1.7
	
//****************************************以上为I/0初始化******************************************
	//使用定时器2作为时钟源
 	
	EAXSFR();		//访问XFR

	PWMCFG = 0x00;	//   7位                     6位             5位    4位    3位    2位    1位    0位 
					//   CBIF
					//1  计数器归零中断标志  计数器归零触发ADC    -      -      -      -      -      -
					//0                      归零时不触发ADC
	
	PWMIF = 0x00;	//  7位    6位  5位   4位   3位   2位   1位   0位 
					//  C7IF  C6IF  C5IF  C4IF  C3IF  C2IF  C1IF  C0IF
					//相应PWM中断标志
	
	PWMFDCR = 0x00;	//  7位     6位   5位     4位    3位    2位   1位   0位 
					// INVCMP  INVIO  ENFD  FLTFLIO  EFDI  FDCMP  FDIO  FDIF

	PWMCKS = 11;	//7位6位5位    4位             3位    2位    1位    0位 
					//   置0    0-系统时钟分频          分频参数设定
					//          1-定时器2溢出       时钟=系统时钟/([3:0]+1)
	
	PWMC  = 16000;	// 15位寄存器，决定PWM周期，数值为1-32767，单位：脉冲时钟
	

// 以下为每个PWM输出口单独设置
	PWM0CR = 0x80;	//     7位      6位        5位   4位3位     2位         1位            0位 
					//     ENCnO    CnINI       -    Cn_S      ECnI       ECnT2SI        ECnT1SI
					//1:   允许PWM  初始高电平       IO选择    允许中断   允许T2点中断   允许T1点中断
					//0:   禁止PWM  初始低电平       IO选择    禁止中断   禁止T2点中断   禁止T1点中断
	PWM1CR = 0x80; 
	PWM2CR = 0x80; 
	PWM3CR = 0x80; 
//	PWM4CR = 0x80; 
//	PWM5CR = 0x80;
//	PWM6CR = 0x80;	
//	PWM7CR = 0x80;
/*	
	PWM0HLD = 0x00;
	PWM1HLD = 0x00;
	PWM2HLD = 0x00;
	PWM3HLD = 0x00;
	PWM4HLD = 0x00;
	PWM5HLD = 0x00;
	PWM6HLD = 0x00;
	PWM7HLD = 0x00;
*/
	PWM0T1 = 6000;
	PWM1T1 = 6000;
	PWM2T1 = 6000;
	PWM3T1 = 6000;
//	PWM4T1 = 4000;
//	PWM5T1 = 4000;
//	PWM6T1 = 4000;
//	PWM7T1 = 4000;

	PWM0T2 = 1000;
	PWM1T2 = 1000;
	PWM2T2 = 1000;
	PWM3T2 = 1000;
//	PWM4T2 = 2000;
//	PWM5T2 = 2000;
//	PWM6T2 = 2000;
//	PWM7T2 = 2000;

	PWMCR = 0x80;	//允许PWM

	EAXRAM();		//恢复访问XRAM

}

