#include "servo.h"
#include "stc8.h"
#include "intrins.h"
#include "delay.h"
#include "uart1.h"

extern char servosend[5];
void spi_servo_senddata(char servoname,char servoang1,char servoang2,char servoang3)
{
servosend[0]='s';
servosend[1]=servoname;
servosend[2]=servoang1;
servosend[3]=servoang2;
servosend[4]=servoang3;

uart2_send(servosend[0]);
uart2_send(servosend[1]);
uart2_send(servosend[2]);
uart2_send(servosend[3]);
uart2_send(servosend[4]);
//uart1_printf("\r\nOK\r\n");
}







	