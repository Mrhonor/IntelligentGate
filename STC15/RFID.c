#include "RFID.h"

#define UART1_BUF_LENGTH 32

char idata RX1_Buffer[UART1_BUF_LENGTH];
char RX1_Cnt = 0;

void RFID_Init(){
    Uart1_Init();
    
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    EA = 1;
    ES = 1;
    REN = 1;
    P67 = 1;             //发送射频使能信号
    SM0 = 0;
    SM1 = 1;
    RI = 0;
}

void Uart1_Init()		//3900bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0x3B;		//设定定时初值
	TH1 = 0xFD;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void UART1_interrupt() interrupt 4
{
    if(RI)
    {
        RX1_Buffer[RX1_Cnt] = SBUF;
        RI = 0;
        if(++RX1_Cnt >= UART1_BUF_LENGTH){
            RX1_Cnt = 0;
            RFID_Check(RX1_Buffer);
        }
    }
}

void RFID_Check(char * msg){}