#include "PCF8563.h"

void PCF8563_Configuration(){
    GPIO_InitTypeDef  gpio;
    
    //ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE); 
    
    
    gpio.GPIO_Pin                        =   GPIO_Pin_14 | GPIO_Pin_15;
    gpio.GPIO_Mode                       =   GPIO_Mode_OUT;
    gpio.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio.GPIO_PuPd                       =   GPIO_PuPd_UP;
    gpio.GPIO_OType                      =   GPIO_OType_OD;  //����Ϊ��©ģʽ����˫��IO
    GPIO_Init(GPIOB, &gpio);
    
}
/*
void EXTI15_10_IRQHandler(void){

}

*/
