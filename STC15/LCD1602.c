#include "LCD1602.h"

void LCD1602_Init(void){
    P0M0 = 0; P0M1 = 0;
    P1M0 = 0; P1M1 = 0;
    P6M0 = 0; P6M1 = 0;
    delay_ms(15);
    LCD1602_Write(0x38, 0);
    delay_ms(5);
    LCD1602_Write(0x38, 0);
    LCD1602_Write(0x08, 0);
    LCD1602_Write(0x01, 0);
    delay_ms(2);           //ÇåÆÁÐèÒª1.64ms
    LCD1602_Write(0x06, 0);
    LCD1602_Write(0x0c, 0);
}

/*
    P05 -- RS 
    P06 -- RW
    P07 -- E
    DB0~DB3 -- P60~P63
    DB4~DB7 -- P12~P15
*/
void LCD1602_Write(unsigned char cmd, char IsData){
    P05 = IsData;
    P06 = 0;
    P07 = 0;
    
    P60 = cmd;
    P61 = cmd >> 1;
    P62 = cmd >> 2;
    P63 = cmd >> 3;
    P12 = cmd >> 4;
    P13 = cmd >> 5;
    P14 = cmd >> 6;
    P15 = cmd >> 7;
    
    delay_us(1);
    
    P07 = 1;
    delay_us(1);
    
    P07 = 0;
    delay_us(1);
}