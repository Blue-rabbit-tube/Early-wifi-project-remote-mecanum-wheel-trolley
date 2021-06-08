#include "stc8.h"
#include "intrins.h"
#include "i2c.h"

#define I2CCFG          (*(unsigned char volatile xdata *)0xfe80)
#define I2CMSCR         (*(unsigned char volatile xdata *)0xfe81)
#define I2CMSST         (*(unsigned char volatile xdata *)0xfe82)
#define I2CSLCR         (*(unsigned char volatile xdata *)0xfe83)
#define I2CSLST         (*(unsigned char volatile xdata *)0xfe84)
#define I2CSLADR        (*(unsigned char volatile xdata *)0xfe85)
#define I2CTXD          (*(unsigned char volatile xdata *)0xfe86)
#define I2CRXD          (*(unsigned char volatile xdata *)0xfe87)

sbit    SDA         =   P1^4;
sbit    SCL         =   P1^5;

void i2c_wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

void i2c_start()
{
    I2CMSCR = 0x01;                             //����START����
    i2c_wait();
}

void i2c_sendData(char dat)
{
    I2CTXD = dat;                               //д���ݵ����ݻ�����
    I2CMSCR = 0x02;                             //����SEND����
    i2c_wait();
}

void i2c_recvACK()
{
    I2CMSCR = 0x03;                             //���Ͷ�ACK����
    i2c_wait();
}

char i2c_recvData()
{
    I2CMSCR = 0x04;                             //����RECV����
    i2c_wait();
    return I2CRXD;
}

void i2c_sendACK()
{
    I2CMSST = 0x00;                             //����ACK�ź�
    I2CMSCR = 0x05;                             //����ACK����
    i2c_wait();
}

void i2c_sendNAK()
{
    I2CMSST = 0x01;                             //����NAK�ź�
    I2CMSCR = 0x05;                             //����ACK����
    i2c_wait();
}

void i2c_stop()
{
    I2CMSCR = 0x06;                             //����STOP����
    i2c_wait();
}

void i2c_init()
{
    P_SW2 = 0x80;
    I2CCFG = 0xe0;                              //ʹ��I2C����ģʽ
    I2CMSST = 0x00;
}
/*
    demo
    demo
    demo
    Start();                                    //������ʼ����
    SendData(0x5a);                             //�����豸��ַ+д����
    RecvACK();
    SendData(0x00);                             //���ʹ洢��ַ
    RecvACK();
    SendData(0x12);                             //д��������1
    RecvACK();
    SendData(0x78);                             //д��������2
    RecvACK();
    Stop();                                     //����ֹͣ����

    Start();                                    //������ʼ����
    SendData(0x5a);                             //�����豸��ַ+д����
    RecvACK();
    SendData(0x00);                             //���ʹ洢��ַ���ֽ�
    RecvACK();
    Start();                                    //������ʼ����
    SendData(0x5b);                             //�����豸��ַ+������
    RecvACK();
    P0 = RecvData();                            //��ȡ����1
    SendACK();
    P2 = RecvData();                            //��ȡ����2
    SendNAK();
    Stop();                                     //����ֹͣ����

    P_SW2 = 0x00;
*/

