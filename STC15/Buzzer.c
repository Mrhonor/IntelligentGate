#include "Buzzer.h"
#define FOSC 18432000L

#define ONEMS (65536 - FOSC/12000)

static volatile unsigned int CountTime = 0;

void Buzzer_Init(void){
    P5M0 = 0; P5M1 = 0;
    P52 = 0;
    
    //��ʱ����ʼ��
    TR0 = 0; 
    AUXR &= 0x7f;  //ѡ�ö�ʱ��0Ϊ12Tģʽ
    TMOD &= 0xF0;   //���ö�ʱ��0Ϊģʽ0
    ET0 = 1;
    EA = 1;
    TH0 = ONEMS >> 8;
    TL0 = ONEMS;
}

void RingTheBuzzer(unsigned int ms){
    TR0 = 1; //��ʼ����
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

