#include "main.h"

char Password[4];
char CurIndex = 0;
char PressNum = 0;

int main()
{   
    RFID_Init();
    KeyBoard_Init();
    LCD1602_Init();
    Photoelectric_Init();
    Buzzer_Init();
    FM25CL64_Init();
    DHT11_Init();
    PCF8563_Init();
    
    while(1){
        //������ⲿ��
        if(KeyBoardCheckFlag && DoorOpenStatus == 0){
            P24 = P25 = P26 = P27 = 1;            
            P24 = 0;
            delay_us(1);   //�ȴ���ƽ�ȶ�
            PressNum = IsAnyKeyPress();
            if(PressNum)
            {
                if(CurIndex < 4)
                {
                    switch(PressNum){
                        case 1:  //�˸�
                            LCD1602_Write(0x80+CurIndex, 0);
                            LCD1602_Write(0xA0, 1);       //��ǰΪд��ո񣬸���֮ǰ����
                            if(CurIndex > 0) CurIndex--;
                            break;
                        case 2:
                            Password[CurIndex] = 1;
                            CurIndex++;
                            break;
                        case 3:
                            Password[CurIndex] = 4;
                            CurIndex++;
                            break;
                        case 4:
                            Password[CurIndex] = 7;
                            CurIndex++;
                            break;    
                        default:
                            break;
                    }
                    LCD1602_Write(0x80+CurIndex, 0);
                    LCD1602_Write(0x30+Password[CurIndex], 1); //��Һ��д������
                }
                //�а�����������0.5s
                RingTheBuzzer(500);
            }   
            P24 = 1;
            P25 = 0;
            delay_us(1);
            PressNum = IsAnyKeyPress();
            if(PressNum)
            {
                if(CurIndex < 4)
                {
                    switch(PressNum){
                        case 1:  
                            Password[CurIndex] = 0;
                            break;
                        case 2:
                            Password[CurIndex] = 2;
                            break;
                        case 3:
                            Password[CurIndex] = 5;
                            break;
                        case 4:
                            Password[CurIndex] = 8;
                            break;    
                        default:
                            break;
                    }
                    LCD1602_Write(0x80+CurIndex, 0);
                    LCD1602_Write(0x30+Password[CurIndex], 1); //��Һ��д������
                    CurIndex++;
                }
                RingTheBuzzer(500);
            }   
            P25 = 1;
            P26 = 0;
            delay_us(1); 
            PressNum = IsAnyKeyPress();
            if(PressNum)
            {
                if(CurIndex < 4)
                {
                    switch(PressNum){
                        case 1:  //ȷ�ϼ�
                            PasswordCheck(Password, CurIndex); //������������Ƿ���ȷ
                            CurIndex = 0;
                            break;
                        case 2:
                            Password[CurIndex] = 1;
                            break;
                        case 3:
                            Password[CurIndex] = 4;
                            break;
                        case 4:
                            Password[CurIndex] = 7;
                            break;    
                        default:
                            break;
                    }
                    if(PressNum != 1){
                        LCD1602_Write(0x80+CurIndex, 0);
                        LCD1602_Write(0x30+Password[CurIndex], 1); //��Һ��д������
                        CurIndex++;
                    }
                }
                else if(CurIndex == 4 && PressNum == 1) //ȷ�ϼ�����
                {
                    PasswordCheck(Password, CurIndex);
                    CurIndex = 0;
                }
                RingTheBuzzer(500);
            }   
            
            // ��ֹ�����쵼��һ�ΰ��¼����
            delay_ms(250);
            delay_ms(250);
        }
        
        //����Ƿ������
        if(abs(SleepTime - IICWriteAndReadData(PCF8563_WRITE_ADD, PCF8563_READ_ADD, 0x03)) > 10){
            Sleep();
        }
        
        if(DoorOpenStatus){
            if(abs(DoorOpenTime - IICWriteAndReadData(PCF8563_WRITE_ADD, PCF8563_READ_ADD, 0x03)) > 2){
                //���ź󳬹�2����δ�ر���,һֱ�������ٴιر�Ϊֹ
                RingTheBuzzer(100);
            }
        }
    }
}

void delay(int time){
    for(; time>0; time--){
    }
}

void delay_ms(unsigned char ms)
{
     unsigned int i;
     do{
          i = MAIN_Fosc / 13000;
          while(--i)    ;   //14T per loop
     }while(--ms);
}

void delay_us(unsigned char us)
{
     unsigned int i;
     do{
          i = MAIN_Fosc / 13000000;
          while(--i > 0)    ;   //14T per loop
     }while(--us);
}

char abs(char num){
    if(num >= 0) return num;
    else return -num;
}
