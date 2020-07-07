#include "Buzzer.h"
#define FOSC 18432000L

#define ONEMS (65536 - FOSC/12000)

static volatile unsigned int CountTime = 0;

void Buzzer_Init(void){
    P5M0 = 0; P5M1 = 0;
    P52 = 0;
    
    //定时器初始化
    TR0 = 0; 
    AUXR &= 0x7f;  //选用定时器0为12T模式
    TMOD &= 0xF0;   //设置定时器0为模式0
    ET0 = 1;
    EA = 1;
    TH0 = ONEMS >> 8;
    TL0 = ONEMS;
}

void RingTheBuzzer(unsigned int ms){
    TR0 = 1; //开始计数
    CountTime = ms;
    P52 = 1;
}

void TIM0_interrupt(void) interrupt 1
{
    if(--CountTime == 0){
        TR0 = 0;
        P52 = 0;
    }
}    

