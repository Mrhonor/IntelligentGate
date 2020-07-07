#include "Photoelectric.h"

char DoorOpenStatus = 0;
char DoorOpenTIme = 0;

void Photoelectric_Init(void){
    P3M0 = 0; P3M1 = 0;
    
    IE0  = 0;   //外中断0标志位
    IT0 = 0;    //INT0 上升沿中断
    EX0 = 1;    //INT0 Enable
    EA = 1;     //允许总中断
}

void INT0_interrupt(void) interrupt 0
{
    //如果门在打开状态收到中断，切换中断为记录上升沿，在关闭状态收到手段，切换中断为记录下降沿
    if(DoorOpenStatus){
        DoorOpenStatus = 0;
        IT0 = 0;
    }
    else{
        DoorOpenTime = IICWriteAndReadData(PCF8563_WRITE_ADD, PCF8563_READ_ADD, 0x03);
        DoorOpenStatus = 1;
        IT0 = 1;
    }
}