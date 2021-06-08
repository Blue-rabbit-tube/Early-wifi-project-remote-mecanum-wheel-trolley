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
    I2CMSCR = 0x01;                             //发送START命令
    i2c_wait();
}

void i2c_sendData(char dat)
{
    I2CTXD = dat;                               //写数据到数据缓冲区
    I2CMSCR = 0x02;                             //发送SEND命令
    i2c_wait();
}

void i2c_recvACK()
{
    I2CMSCR = 0x03;                             //发送读ACK命令
    i2c_wait();
}

char i2c_recvData()
{
    I2CMSCR = 0x04;                             //发送RECV命令
    i2c_wait();
    return I2CRXD;
}

void i2c_sendACK()
{
    I2CMSST = 0x00;                             //设置ACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    i2c_wait();
}

void i2c_sendNAK()
{
    I2CMSST = 0x01;                             //设置NAK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    i2c_wait();
}

void i2c_stop()
{
    I2CMSCR = 0x06;                             //发送STOP命令
    i2c_wait();
}

void i2c_init()
{
    P_SW2 = 0x80;
    I2CCFG = 0xe0;                              //使能I2C主机模式
    I2CMSST = 0x00;
}
/*
    demo
    demo
    demo
    Start();                                    //发送起始命令
    SendData(0x5a);                             //发送设备地址+写命令
    RecvACK();
    SendData(0x00);                             //发送存储地址
    RecvACK();
    SendData(0x12);                             //写测试数据1
    RecvACK();
    SendData(0x78);                             //写测试数据2
    RecvACK();
    Stop();                                     //发送停止命令

    Start();                                    //发送起始命令
    SendData(0x5a);                             //发送设备地址+写命令
    RecvACK();
    SendData(0x00);                             //发送存储地址高字节
    RecvACK();
    Start();                                    //发送起始命令
    SendData(0x5b);                             //发送设备地址+读命令
    RecvACK();
    P0 = RecvData();                            //读取数据1
    SendACK();
    P2 = RecvData();                            //读取数据2
    SendNAK();
    Stop();                                     //发送停止命令

    P_SW2 = 0x00;
*/

