#include "Keyboard.h"

void KeyBoard_Configuration(){
    GPIO_InitTypeDef  gpio_in;
    GPIO_InitTypeDef  gpio_out;
    GPIO_InitTypeDef  gpio_nvic;
    
    NVIC_InitTypeDef  nvic;
    EXTI_InitTypeDef  exti;
    
    //ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,  ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    //���������
    gpio_in.GPIO_Pin                        =   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    gpio_in.GPIO_Mode                       =   GPIO_Mode_IN;
    gpio_in.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio_in.GPIO_PuPd                       =   GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &gpio_in);
    
    //������ѯ��ѯ��
    gpio_out.GPIO_Pin                       =   GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    gpio_out.GPIO_Mode                      =   GPIO_Mode_OUT;
    gpio_out.GPIO_OType                     =   GPIO_OType_PP;
    gpio_out.GPIO_Speed                     =   GPIO_Speed_2MHz;
    gpio_out.GPIO_PuPd                      =   GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &gpio_out);
    
    //�����жϿ�
    gpio_nvic.GPIO_Pin                        =   GPIO_Pin_15;
    gpio_nvic.GPIO_Mode                       =   GPIO_Mode_IN;
    gpio_nvic.GPIO_Speed                      =   GPIO_Speed_2MHz;
    gpio_nvic.GPIO_PuPd                       =   GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &gpio_nvic);
    
    //�ж�����
    nvic.NVIC_IRQChannel                    = EXTI15_10_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority  = 0;
    nvic.NVIC_IRQChannelSubPriority         = 0;
    nvic.NVIC_IRQChannelCmd                 = ENABLE;
    NVIC_Init(&nvic);    
    
    //�ж�Դ����
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource15);
    
    exti.EXTI_Line    = EXTI_Line15;
    exti.EXTI_Mode    = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling; //ѡ���½��ش���
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
    
    //Ĭ������͵�ƽ
    GPIOD->BSRRL = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
}
/*
void EXTI15_10_IRQHandler(void){

}

*/
