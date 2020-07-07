#include "KeyBoard.h"
// P2.0~P2.7�������� P3.3���ⲿ�ж�

volatile char KeyBoardCheckFlag = 0;
char CorrectPassword[4] = {1,2,3,4};

void KeyBoard_Init(void){
    //����Ϊ׼˫���
    P2M0 = 0; P2M1 = 0; 
    P3M0 = 0; P3M1 = 0; 
    
    P24 = P25 = P26 = P27 = 0;
    
    IE1  = 0;   //���ж�1��־λ
    IT1 = 1;    //INT1 �½����ж�
    EX1 = 1;    //INT1 Enable
    EA = 1;     //�������ж�
    
}

void INT1_interrupt(void) interrupt 2
{
    //��ʼ������
    KeyBoardCheckFlag = 1;
    
    //����LCD��Ļ
    LCD1602_Init();
    
    //ʹ��RFID��Ƶ
    P67 = 1; 
    
    //��������ʱ��
    SleepTimeReset();
    
}

void SleepTimeReset(void){
    //��ȡPCF8563�ķ��ӼĴ�����ֵ
    SleepTime = IICWriteAndReadData(PCF8563_WRITE_ADD, PCF8563_READ_ADD, 0x03); 
}

void Sleep(void){
    KeyBoardCheckFlag = 0;
    LCD1602_Write(0x01, 0);
    delay_ms(2);           //������Ҫ1.64ms
}

char IsAnyKeyPress(void){
    if(P20 == 0){
        delay(1000); //��ʱ���ٴμ��
        if(P20 == 0) return 1;
    }
    
    if(P21 == 0){
        delay(1000); //��ʱ���ٴμ��
        if(P21 == 0) return 2;
    }
    
    if(P22 == 0){
        delay(1000); //��ʱ���ٴμ��
        if(P22 == 0) return 3;
    }

    if(P23 == 0){
        delay(1000); //��ʱ���ٴμ��
        if(P23 == 0) return 4;
    }
    
    return 0;
}

unsigned char Welcome[7] = {'W', 'E', 'L', 'C', 'O', 'M', 'E'};

void PasswordCheck(char* Password, char num){
    char index;
    for(index = 0; index < num; index++){
        if(Password[index] != CorrectPassword[index]) {
            LCD1602_Write(0x01, 0);  //��������
            delay_ms(2);             //������ʱ1.64ms��������ʱһ��ʱ��
            return;
        }
    }
    
    //������ȷ����ʾ ��WELCOME�� ����
    for(index = 0; index < 7; index++){
        LCD1602_Write(0x80+index, 0);
        LCD1602_Write(Welcome[index], 1);
    }
    
    
    // ���ÿ��ų���
    
}
