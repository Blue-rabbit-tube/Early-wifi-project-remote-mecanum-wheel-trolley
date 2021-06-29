
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU RC Demo -----------------------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/


#ifndef	__PCA_H
#define	__PCA_H

#include	"config.h"

#define	PCA0			0
#define	PCA1			1
#define	PCA2			2
#define	PCA3			3
#define	PCA_Counter		4
#define	PCA_P12_P17_P16_P15_P14	(0<<4)
#define	PCA_P22_P23_P24_P25_P26	(1<<4)
#define	PCA_P74_P70_P71_P72_P73	(2<<4)
#define	PCA_P35_P33_P32_P31_P30	(3<<4)

#define	PCA_Mode_PWM				0x42	//B0100_0010
#define	PCA_Mode_Capture			0
#define	PCA_Mode_SoftTimer			0x48	//B0100_1000
#define	PCA_Mode_HighPulseOutput	0x4c	//B0100_1100
#define	PCA_Clock_1T	(4<<1)
#define	PCA_Clock_2T	(1<<1)
#define	PCA_Clock_4T	(5<<1)
#define	PCA_Clock_6T	(6<<1)
#define	PCA_Clock_8T	(7<<1)
#define	PCA_Clock_12T	(0<<1)
#define	PCA_Clock_Timer0_OF	(2<<1)
#define	PCA_Clock_ECI	(3<<1)
#define	PCA_Rise_Active	(1<<5)
#define	PCA_Fall_Active	(1<<4)
#define	PCA_PWM_8bit	(0<<6)
#define	PCA_PWM_7bit	(1<<6)
#define	PCA_PWM_6bit	(2<<6)
#define	PCA_PWM_10bit	(3<<6)


typedef struct
{
	u8	PCA_IoUse;		//PCA_P12_P17_P16_P15_P14, PCA_P22_P23_P24_P25_P26, PCA_P74_P70_P71_P72_P73, PCA_P35_P33_P32_P31_P30
	u8	PCA_Clock;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	u8	PCA_Mode;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	u8	PCA_PWM_Wide;	//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
	u8	PCA_Interrupt_Mode;	//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	u8	PCA_Polity;	//���ȼ�����	PolityHigh,PolityLow
	u16	PCA_Value;
	u8	PCA_RUN;	//ENABLE, DISABLE
} PCA_InitTypeDef;

extern	bit		B_Capture0,B_Capture1,B_Capture2,B_Capture3;
extern	u8		PCA0_mode,PCA1_mode,PCA2_mode,PCA3_mode;
extern	u16		CCAP0_tmp,PCA_Timer0;
extern	u16		CCAP1_tmp,PCA_Timer1;
extern	u16		CCAP2_tmp,PCA_Timer2;
extern	u16		CCAP3_tmp,PCA_Timer3;
void	PCA_Init(u8 PCA_id, PCA_InitTypeDef *PCAx);
void	UpdatePwm(u8 PCA_id, u16 pwm_value);


#endif

