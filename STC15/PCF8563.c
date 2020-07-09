#include "PCF8563.h"

// P70 -- SCL  P71 -- SDA
#define SDA P71
#define SCL P70

void PCF_Init(void){
    P7M0 = 0; P7M1 = 0;
    //����PCF8563
    IICWriteData(PCF8563_WRITE_ADD, 0x00, 0x00);
}

//�ȴ�Ӧ��
char WaitForAcknowledgement(void){
    SDA = 1;
    delay_us(1);             
    SCL = 1;
    delay_us(1);
    if(SDA)
    { 
       StopIIC();
       return 0;
    }
    SCL = 0;
    delay_us(2);
    return 1;
}

//��ʼ�ź�
void StartIIC(void){
    SCL = 1;
    delay_us(1);
    SDA = 1;
    delay_us(1);
    SDA = 0;
    delay_us(1);
}

//��ֹ�ź�
void StopIIC(void){
    SCL = 0;
    delay_us(2);  //����ʱ��������͵�ƽҪ����1.3��s
    SDA = 0;
    delay_us(1);
    SCL = 1;
    delay_us(1);
    SDA = 1;
    delay_us(4); //ֹͣ�ź�����Ҫ����4��s
}

//����һ��bit
void SendBit(unsigned char bitValue){
    SCL = 0;
    delay_us(2);
    SDA = bitValue;
    delay_us(1);
    SCL = 1;
    delay_us(1);
    SCL = 0;
    delay_us(2);
}

void IICWriteData(unsigned char SlaveAdd, unsigned char Add, unsigned char Data){
    unsigned char i;
    StartIIC();

    for(i = 0; i < 7; i++){
        SendBit(SlaveAdd >> i);
    }
    SendBit(0); //��дλ
    
    if(!WaitForAcknowledgement()) return; //δ�յ�Ӧ�����ͨ��
    
    for(i = 0; i < 8; i++){
        SendBit(Add >> i);
    }
    
    if(!WaitForAcknowledgement()) return; //δ�յ�Ӧ�����ͨ��
    
    for(i = 0; i < 8; i++){
        SendBit(Data >> i);
    }
      
    if(!WaitForAcknowledgement()) return; //δ�յ�Ӧ�����ͨ��
    
    StopIIC();
}

char IICWriteAndReadData(unsigned char SlaveWriteAdd, unsigned char Add, unsigned char SlaveReadAdd){
    unsigned char i;
    unsigned char Data = 0;

    StartIIC();
    
    for(i = 0; i < 7; i++){
        SendBit(SlaveWriteAdd >> i);
    }
    SendBit(0); //��дλ
    
    if(!WaitForAcknowledgement()) return -1; //δ�յ�Ӧ�����ͨ��
    
    for(i = 0; i < 8; i++){
        SendBit(Add >> i);
    }
    
    if(!WaitForAcknowledgement()) return -1; //δ�յ�Ӧ�����ͨ��
    
    StartIIC();
    for(i = 0; i < 7; i++){
        SendBit(SlaveReadAdd >> i);
    }
    SendBit(1); //��дλ
    
    if(!WaitForAcknowledgement()) return -1; //δ�յ�Ӧ�����ͨ��
    

    
    while(SCL){
        Data = Data | ((SDA && 0xFF) << i);
        i++;
    }
    
    StopIIC();

    return BCDtoData(Data);
}

char BCDtoData(unsigned char Data){
    // BCD��ת������
    return 0;
}