#include "FM25CL64.h"

void FM25CL64_Configuration(){
    GPIO_InitTypeDef  gpio;
    
    //Ê±ÖÓÊ¹ÄÜ
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE); 
    
    
    gpio.GPIO_Pin                        =   GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    gpio.GPIO_Mode                       =   GPIO_Mode_OUT;
    gpio.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio.GPIO_PuPd                       =   GPIO_PuPd_UP;
    gpio.GPIO_OType                      =   GPIO_OType_OD;
    GPIO_Init(GPIOB, &gpio);
    
    GPIOB->BSRRH = GPIO_Pin_11;
    GPIOB->BSRRL = GPIO_Pin_8;
}

