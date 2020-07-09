#include "Photoelectric.h"

void Photoelectric_Configuration(){
    GPIO_InitTypeDef  gpio;
    
    NVIC_InitTypeDef  nvic;
    EXTI_InitTypeDef  exti;
    
    //ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,  ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    gpio.GPIO_Pin                        =   GPIO_Pin_0;
    gpio.GPIO_Mode                       =   GPIO_Mode_IN;
    gpio.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio.GPIO_PuPd                       =   GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &gpio);
   
    
    //�ж�����
    nvic.NVIC_IRQChannel                    = EXTI0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority  = 0;
    nvic.NVIC_IRQChannelSubPriority         = 0;
    nvic.NVIC_IRQChannelCmd                 = ENABLE;
    NVIC_Init(&nvic);    
    
    //�ж�Դ����
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
    
    exti.EXTI_Line    = EXTI_Line0;
    exti.EXTI_Mode    = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //ѡ�������غ��½��ض�����
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
 
}
/*
void EXTI0_IRQHandler(void){

}

*/
