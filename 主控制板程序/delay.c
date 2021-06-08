void delay_ms(int mstime)		//@27.000MHz
{
int mstimenow;
for(mstimenow=1;mstimenow<=mstime;mstimenow++)
{	unsigned char i, j;

	i = 27;
	j = 64;
	do
	{
		while (--j);
	} while (--i);}
}