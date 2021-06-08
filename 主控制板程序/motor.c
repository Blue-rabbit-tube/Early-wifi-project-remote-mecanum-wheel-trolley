#include "stc8.h"
#include "motor.h"
/*************************************************
              Pin to motor list
P00 P01      P02 P03     P04 P05     P06 P07        function
P32          P33         P34         P40            en/disable
LB           RB          LF          RF

Pwm is always on.
By controling the en pin to control the motor.
*************************************************/
#define pwmlb P00
#define pwmrb P02
#define pwmlf P04
#define pwmrf P06

#define udlb P01
#define udrb P03
#define udlf P05
#define udrf P07

#define enlb P32
#define enrb P33
#define enlf P34
#define enrf P40

void motor_clock_init()        //  800us a period
{
    TMOD = 0x00;
    TL0 = 0x36;                      
    TH0 = 0xf7;
    TR0 = 1;                                   
    ET0 = 1;                                 
    EA = 1;
}

void motor_clock_pin() interrupt 1
{
P42=!P42;
pwmlb=!pwmlb;
pwmrb=!pwmrb;
pwmlf=!pwmlf;
pwmrf=!pwmrf;
}


//lb
void uplbs()
{enlb=0;
udlb=1;}
void downlbs()
{enlb=0;
udlb=0;}
void stoplbs()
{enlb=1;
udlb=1;}


//rb
void uprbs()
{enrb=0;
udrb=0;}
void downrbs()
{enrb=0;
udrb=1;}
void stoprbs()
{enrb=1;
udrb=1;}


//lf	
void uplfs()
{enlf=0;
udlf=1;}
void downlfs()
{enlf=0;
udlf=0;}
void stoplfs()
{enlf=1;
udlf=1;}


//rf
void uprfs()
{enrf=0;
udrf=0;}
void downrfs()
{enrf=0;
udrf=1;}
void stoprfs()
{enrf=1;
udrf=1;}





//total
void motor_up()
{
uplbs();
uprbs();
uplfs();
uprfs();
}
void motor_down()
{
downlbs();
downrbs();
downlfs();
downrfs();
}
void motor_left()
{
downlbs();
uprbs();
uplfs();
downrfs();
}
void motor_right()
{
uplbs();
downrbs();
downlfs();
uprfs();
}
void motor_stop()
{
stoplbs();
stoprbs();
stoplfs();
stoprfs();
}
void motor_lc()
{
downlbs();
uprbs();
downlfs();
uprfs();
}
void motor_rc()
{
uplbs();
downrbs();
uplfs();
downrfs();
}
