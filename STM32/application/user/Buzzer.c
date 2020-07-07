#include "Buzzer.h"

void Buzzer_Configuration(){
    GPIO_InitTypeDef  gpio;
    
    // ±÷” πƒ‹
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE); 
    
    
    gpio.GPIO_Pin                        =   GPIO_Pin_13;
    gpio.GPIO_Mode                       =   GPIO_Mode_OUT;
    gpio.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio.GPIO_PuPd                       =   GPIO_PuPd_UP;
    gpio.GPIO_OType                      =   GPIO_OType_PP;
    GPIO_Init(GPIOB, &gpio);
    
}

