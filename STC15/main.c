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
        //按键检测部分
        if(KeyBoardCheckFlag && DoorOpenStatus == 0){
            P24 = P25 = P26 = P27 = 1;            
            P24 = 0;
            delay_us(1);   //等待电平稳定
            PressNum = IsAnyKeyPress();
            if(PressNum)
            {
                if(CurIndex < 4)
                {
                    switch(PressNum){
                        case 1:  //退格
                            LCD1602_Write(0x80+CurIndex, 0);
                            LCD1602_Write(0xA0, 1);       //向当前为写入空格，覆盖之前输入
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
                    LCD1602_Write(0x30+Password[CurIndex], 1); //向液晶写入数字
                }
                //有按键按下响铃0.5s
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
                    LCD1602_Write(0x30+Password[CurIndex], 1); //向液晶写入数字
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
                        case 1:  //确认键
                            PasswordCheck(Password, CurIndex); //检测密码输入是否正确
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
                        LCD1602_Write(0x30+Password[CurIndex], 1); //向液晶写入数字
                        CurIndex++;
                    }
                }
                else if(CurIndex == 4 && PressNum == 1) //确认键按下
                {
                    PasswordCheck(Password, CurIndex);
                    CurIndex = 0;
                }
                RingTheBuzzer(500);
            }   
            
            // 防止检测过快导致一次按下检测多个
            delay_ms(250);
            delay_ms(250);
        }
        
        //检测是否该休眠
        if(abs(SleepTime - IICWriteAndReadData(PCF8563_WRITE_ADD, PCF8563_READ_ADD, 0x03)) > 10){
            Sleep();
        }
        
        if(DoorOpenStatus){
            if(abs(DoorOpenTime - IICWriteAndReadData(PCF8563_WRITE_ADD, PCF8563_READ_ADD, 0x03)) > 2){
                //打开门后超过2分钟未关报警,一直报警到再次关闭为止
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
