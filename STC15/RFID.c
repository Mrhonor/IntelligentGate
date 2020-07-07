#include "RFID.h"

#define UART1_BUF_LENGTH 32

char idata RX1_Buffer[UART1_BUF_LENGTH];
char RX1_Cnt = 0;

void RFID_Init(){
    Uart1_Init();
    
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    EA = 1;
    ES = 1;
    REN = 1;
    P67 = 1;             //������Ƶʹ���ź�
    SM0 = 0;
    SM1 = 1;
    RI = 0;
}

void Uart1_Init()		//3900bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0x3B;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
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