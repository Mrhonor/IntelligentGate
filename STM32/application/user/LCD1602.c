#include "LCD1602.h"

void LCD1602_Configuration(){
    GPIO_InitTypeDef  gpio;
    
    //时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,  ENABLE); 
    
    
    gpio.GPIO_Pin                        =   GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    gpio.GPIO_Mode                       =   GPIO_Mode_OUT;
    gpio.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio.GPIO_PuPd                       =   GPIO_PuPd_UP;
    gpio.GPIO_OType                      =   GPIO_OType_OD;  //设置为开漏模式可以双向IO
    GPIO_Init(GPIOC, &gpio);
    
}
/*
void EXTI15_10_IRQHandler(void){

}

*/
