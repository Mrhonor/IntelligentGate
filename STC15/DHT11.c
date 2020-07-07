#include "DHT11.h"
float Temperature = 0.0f;
float Humidity = 0.0f;

static char Data[5];


void DHT11_Init(void){
    P7M0 = 0; P7M1 = 0;
    P75 = 1;
}

void GetDHTData(void){
    unsigned char WaitTime;
    char DataCount;
    
    P75 = 1;
    delay_us(1);
    
    P75 = 0;
    delay_ms(20);
    
    P75 = 1;
    
    WaitTime = 100;
    while(P75){
        if(--WaitTime <= 0) return;
    }
    
    WaitTime = 150;
    while(!P75){
        if(--WaitTime <= 0) return;
    }
        
    DataCount = 40;
    while(DataCount--){
        //�ȴ��͵�ƽ�ź�
        while(P75);
        while(!P75);
        WaitTime = 0;
        while(P75) WaitTime++;
        if(WaitTime > 50) Data[4-DataCount/8] |=   1 << (DataCount % 8); 
        else              Data[4-DataCount/8] &= ~(1 << (DataCount % 8));           
    }
    
    while(P75);
    delay_us(50);
    P75 = 1;
    
    //����У��λ�������
    if(((Data[0]+Data[1]+Data[2]+Data[3]) & 0xFF) == Data[4]){
        Unpack();
    }
}

void Unpack(void){
}
