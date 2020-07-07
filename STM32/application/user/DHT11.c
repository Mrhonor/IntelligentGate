#include "DHT11.h"

void DHT11_Configuration(){
    GPIO_InitTypeDef  gpio;
    
    // ±÷” πƒ‹
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE); 
    
    
    gpio.GPIO_Pin                        =   GPIO_Pin_12;
    gpio.GPIO_Mode                       =   GPIO_Mode_OUT;
    gpio.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio.GPIO_PuPd                       =   GPIO_PuPd_UP;
    gpio.GPIO_OType                      =   GPIO_OType_OD;
    GPIO_Init(GPIOB, &gpio);
    
}
