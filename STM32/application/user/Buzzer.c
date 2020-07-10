#include "Buzzer.h"

void Buzzer_Configuration(){
    GPIO_InitTypeDef         gpio;
    NVIC_InitTypeDef         nvic;
    TIM_TimeBaseInitTypeDef  tim;
    
    
    //ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,  ENABLE); 
    
    
    gpio.GPIO_Pin                        =   GPIO_Pin_13;
    gpio.GPIO_Mode                       =   GPIO_Mode_OUT;
    gpio.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio.GPIO_PuPd                       =   GPIO_PuPd_UP;
    gpio.GPIO_OType                      =   GPIO_OType_PP;
    GPIO_Init(GPIOB, &gpio);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    
    nvic.NVIC_IRQChannel                   = TIM6_DAC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority        = 0;
    nvic.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&nvic);
    
    tim.TIM_Period                         = 84000;
    tim.TIM_Prescaler                      = 999;

    //��������жϱ�־λ
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    
    //������ʱ�������жϱ�־λ
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    
    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM6, ENABLE);
}

