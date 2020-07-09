#include "Keyboard.h"

void KeyBoard_Configuration(){
    GPIO_InitTypeDef  gpio_in;
    GPIO_InitTypeDef  gpio_out;
    GPIO_InitTypeDef  gpio_nvic;
    
    NVIC_InitTypeDef  nvic;
    EXTI_InitTypeDef  exti;
    
    //时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,  ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    //键盘输入口
    gpio_in.GPIO_Pin                        =   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    gpio_in.GPIO_Mode                       =   GPIO_Mode_IN;
    gpio_in.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio_in.GPIO_PuPd                       =   GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &gpio_in);
    
    //键盘轮询查询口
    gpio_out.GPIO_Pin                       =   GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    gpio_out.GPIO_Mode                      =   GPIO_Mode_OUT;
    gpio_out.GPIO_OType                     =   GPIO_OType_PP;
    gpio_out.GPIO_Speed                     =   GPIO_Speed_2MHz;
    gpio_out.GPIO_PuPd                      =   GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &gpio_out);
    
    //键盘中断口
    gpio_nvic.GPIO_Pin                        =   GPIO_Pin_15;
    gpio_nvic.GPIO_Mode                       =   GPIO_Mode_IN;
    gpio_nvic.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio_nvic.GPIO_PuPd                       =   GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &gpio_nvic);
    
    //中断配置
    nvic.NVIC_IRQChannel                    = EXTI15_10_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority  = 0;
    nvic.NVIC_IRQChannelSubPriority         = 0;
    nvic.NVIC_IRQChannelCmd                 = ENABLE;
    NVIC_Init(&nvic);    
    
    //中断源连接
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource15);
    
    exti.EXTI_Line    = EXTI_Line15;
    exti.EXTI_Mode    = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling; //选择下降沿触发
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
    
    //默认输出低电平
    GPIOD->BSRRL = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
}
/*
void EXTI15_10_IRQHandler(void){

}

*/
