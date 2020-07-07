#include "Photoelectric.h"

char DoorOpenStatus = 0;
char DoorOpenTIme = 0;

void Photoelectric_Init(void){
    P3M0 = 0; P3M1 = 0;
    
    IE0  = 0;   //���ж�0��־λ
    IT0 = 0;    //INT0 �������ж�
    EX0 = 1;    //INT0 Enable
    EA = 1;     //�������ж�
}

void INT0_interrupt(void) interrupt 0
{
    //������ڴ�״̬�յ��жϣ��л��ж�Ϊ��¼�����أ��ڹر�״̬�յ��ֶΣ��л��ж�Ϊ��¼�½���
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