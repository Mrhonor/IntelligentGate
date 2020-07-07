#include "KeyBoard.h"
// P2.0~P2.7用作键盘 P3.3作外部中断

volatile char KeyBoardCheckFlag = 0;
char CorrectPassword[4] = {1,2,3,4};

void KeyBoard_Init(void){
    //设置为准双向口
    P2M0 = 0; P2M1 = 0; 
    P3M0 = 0; P3M1 = 0; 
    
    P24 = P25 = P26 = P27 = 0;
    
    IE1  = 0;   //外中断1标志位
    IT1 = 1;    //INT1 下降沿中断
    EX1 = 1;    //INT1 Enable
    EA = 1;     //允许总中断
    
}

void INT1_interrupt(void) interrupt 2
{
    //开始检测键盘
    KeyBoardCheckFlag = 1;
    
    //唤醒LCD屏幕
    LCD1602_Init();
    
    //使能RFID射频
    P67 = 1; 
    
    //重置休眠时间
    SleepTimeReset();
    
}

void SleepTimeReset(void){
    //读取PCF8563的分钟寄存器的值
    SleepTime = IICWriteAndReadData(PCF8563_WRITE_ADD, PCF8563_READ_ADD, 0x03); 
}

void Sleep(void){
    KeyBoardCheckFlag = 0;
    LCD1602_Write(0x01, 0);
    delay_ms(2);           //清屏需要1.64ms
}

char IsAnyKeyPress(void){
    if(P20 == 0){
        delay(1000); //延时后再次检测
        if(P20 == 0) return 1;
    }
    
    if(P21 == 0){
        delay(1000); //延时后再次检测
        if(P21 == 0) return 2;
    }
    
    if(P22 == 0){
        delay(1000); //延时后再次检测
        if(P22 == 0) return 3;
    }

    if(P23 == 0){
        delay(1000); //延时后再次检测
        if(P23 == 0) return 4;
    }
    
    return 0;
}

unsigned char Welcome[7] = {'W', 'E', 'L', 'C', 'O', 'M', 'E'};

void PasswordCheck(char* Password, char num){
    char index;
    for(index = 0; index < num; index++){
        if(Password[index] != CorrectPassword[index]) {
            LCD1602_Write(0x01, 0);  //出错清屏
            delay_ms(2);             //清屏用时1.64ms，所以延时一定时间
            return;
        }
    }
    
    //密码正确，显示 “WELCOME” 字样
    for(index = 0; index < 7; index++){
        LCD1602_Write(0x80+index, 0);
        LCD1602_Write(Welcome[index], 1);
    }
    
    
    // 调用开门程序
    
}
