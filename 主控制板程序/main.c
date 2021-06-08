#include "stc8.h"
#include "intrins.h"
#include "uart2.h"
#include "i2c.h"
#include "servo.h"
#include "delay.h"
#include "motor.h"
#include "uart1.h"

char uart2buf[50]="0";
extern int uart2datacount;
int uart2datasearch=0;
char servodata[8];
char servonumber;
int uart2servonumber=0;
char servosend[5];
int servosendnm=0;

void uart2_wifi_init()
{
delay_ms(3500);
uart2_printf("AT+CIPMUX=1\r\n");
delay_ms(1000);
uart2_printf("AT+CIPSERVER=1,23\r\n");
}


void init()                         //starting init
{
uart1_init();
uart2_init();
uart2_wifi_init();
motor_clock_init();
motor_stop();
}


	


void main()
{

init();
	
while(1)
{
for(uart2datasearch=0;uart2datasearch<=30;uart2datasearch++)
{
	//up
	if(uart2buf[uart2datasearch]=='u')
	{	if(uart2buf[uart2datasearch+1]=='p')
{
	 motor_up();
   uart2_printf("AT+CIPSEND=0,3\r\n");
	 delay_ms(100);
	 uart2_printf("ok\r\n");
	 delay_ms(100);
}
}
	//do
if(uart2buf[uart2datasearch]=='d')
	{	if(uart2buf[uart2datasearch+1]=='o')
{
	 motor_down();
   uart2_printf("AT+CIPSEND=0,3\r\n");
	 delay_ms(100);
	 uart2_printf("ok\r\n");
	 delay_ms(100);
}
}
//lf
if(uart2buf[uart2datasearch]=='l')
	{	if(uart2buf[uart2datasearch+1]=='f')
{
	 motor_left();
   uart2_printf("AT+CIPSEND=0,3\r\n");
	 delay_ms(100);
	 uart2_printf("ok\r\n");
	 delay_ms(100);
}
}
//ri
if(uart2buf[uart2datasearch]=='r')
	{	if(uart2buf[uart2datasearch+1]=='i')
{
	 motor_right();
   uart2_printf("AT+CIPSEND=0,3\r\n");
	 delay_ms(100);
	 uart2_printf("ok\r\n");
	 delay_ms(100);
}
}
//st
if(uart2buf[uart2datasearch]=='s')
	{	if(uart2buf[uart2datasearch+1]=='t')
{
	 motor_stop();
   uart2_printf("AT+CIPSEND=0,3\r\n");
	 delay_ms(100);
	 uart2_printf("ok\r\n");
	 delay_ms(100);
}
}
//lc
if(uart2buf[uart2datasearch]=='l')
	{	if(uart2buf[uart2datasearch+1]=='c')
{
	 motor_lc();
   uart2_printf("AT+CIPSEND=0,3\r\n");
	 delay_ms(100);
	 uart2_printf("ok\r\n");
	 delay_ms(100);
}
}
//rc
if(uart2buf[uart2datasearch]=='r')
	{	if(uart2buf[uart2datasearch+1]=='c')
{
	 motor_rc();
   uart2_printf("AT+CIPSEND=0,3\r\n");
	 delay_ms(100);
	 uart2_printf("ok\r\n");
	 delay_ms(100);
}
}
//se
if(uart2buf[uart2datasearch]=='s')
	{	if(uart2buf[uart2datasearch+1]=='e')
{
	    for(servosendnm=0;servosendnm<=20;servosendnm++)
     {
			 delay_ms(1);
			 spi_servo_senddata(uart2buf[uart2datasearch+2],uart2buf[uart2datasearch+3],uart2buf[uart2datasearch+4],uart2buf[uart2datasearch+5]);
		 }
		 uart2buf[uart2datasearch+1]='p';
	   
  /*  uart2buf[uart2datasearch+1]='p';           //uart1 and uart2 don't be used at the same time . A unknow bug.
	    uart2_printf("AT+CIPSEND=0,3\r\n");
	    delay_ms(100);
	    uart2_printf("KO\r\n");
	    delay_ms(100);  */
}
}


}
}}


