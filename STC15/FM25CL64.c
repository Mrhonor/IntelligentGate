#include "FM25CL64.h"

#define SCK P74
#define SI P76
#define SO P77
#define CS P45

#define WREN  0x06
#define READ  0x03
#define WRITE 0x02

void FM25CL64_Init(void){
    P7M0 = 0; P7M1 = 0;
    P4M0 = 0; P4M1 = 0;
    
    SCK = 0;
    CS = 1;
}

void SPIWriteData(unsigned char Data, unsigned int add){
    CS = 0;
    delay_us(1);
    SendData(WREN);     //����дʹ��
    CS = 1;
    delay_us(1);
    CS = 0;
    delay_us(1);
    SendData(WRITE);    //����д����
    SendData(add >> 8); //���͸߰�λ��ַ
    SendData(add);      //���͵Ͱ�λ��ַ   
    SendData(Data);     //��������
    CS = 1;
    delay_us(1);
}

unsigned char SPIReadData(unsigned int add){
    unsigned char ReturnData;
    CS = 0;
    delay_us(1);
    SendData(READ);              //���Ͷ�����
    SendData(add >> 8);          //���͸߰�λ��ַ
    SendData(add);               //���͵Ͱ�λ��ַ   
    ReturnData = ReadData();     //��������
    CS = 1;
    delay_us(1);
    return ReturnData;
}

void SendData(unsigned char Data){
    char i;
    SCK = 0;
    for(i = 7; i>=0; i--){
        SI = Data >> i;
        nop();
        SCK = 1;
        nop();
        SCK = 0;
    }
}

unsigned char ReadData(void){
    unsigned char Data;
    char i;
    for(i = 7; i>=0; i--){
        while(!SCK);
        nop();
        if(SO == 0){
            Data &= ~(1 << i);
        }
        else{
            Data |=  (1 << i);
        }
    }
    return Data;
}
