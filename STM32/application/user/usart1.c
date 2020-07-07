#include "usart1.h"

/*-----USART1_RX-----PA5----*/ 

#define USART1_RX_BUF_LEN 32



static char USART1_RX_BUFFER[USART1_RX_BUF_LEN];

static int Rx_Cut = 0;

void USART1_Configuration(){
    GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;
    USART_InitTypeDef usart;
    
    GPIO_InitTypeDef  gpio_cfe;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,  ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    //配置与RFID通信的RX口
    gpio.GPIO_Pin                           =   GPIO_Pin_10;
    gpio.GPIO_Mode                          =   GPIO_Mode_AF;
    gpio.GPIO_Speed                         =   GPIO_Speed_2MHz;
    gpio.GPIO_PuPd                          =   GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &gpio);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    
    //控制RFID射频使能的IO口
    gpio_cfe.GPIO_Pin                       =   GPIO_Pin_6;
    gpio_cfe.GPIO_Mode                      =   GPIO_Mode_OUT;
    gpio_cfe.GPIO_OType                     =   GPIO_OType_PP;
    gpio_cfe.GPIO_Speed                     =   GPIO_Speed_2MHz;
    gpio_cfe.GPIO_PuPd                      =   GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &gpio_cfe);
    //输出高电平
    GPIOA->BSRRH = GPIO_Pin_6;
    
    usart.USART_BaudRate                    =   3900;
    usart.USART_WordLength                  =   USART_WordLength_8b;
    usart.USART_StopBits                    =   USART_StopBits_1;
    usart.USART_Parity                      =   USART_Parity_No;   
    usart.USART_Mode                        =   USART_Mode_Rx;
    usart.USART_HardwareFlowControl         =   USART_HardwareFlowControl_None;
    USART_Init(USART1, &usart);
    
    nvic.NVIC_IRQChannel                    = USART1_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority  = 0;
    nvic.NVIC_IRQChannelSubPriority         = 0;
    nvic.NVIC_IRQChannelCmd                 = ENABLE;
    NVIC_Init(&nvic);    
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
}

void USART1_IRQHandler(void){
    char RxTemp;
    if(USART_GetITStatus(USART1, USART_IT_RXNE)!= RESET){
        RxTemp = USART_ReceiveData(USART1);
 
        USART1_RX_BUFFER[Rx_Cut] = RxTemp;
        Rx_Cut++;
        if(Rx_Cut >= USART1_RX_BUF_LEN){
            RFID_Check(USART1_RX_BUFFER);
            Rx_Cut = 0;
        }
        //clear the RXNE pending flag 
        (void)USART1->SR;
        (void)USART1->DR;
    }
    
}

void RFID_Check(char * msg){
}
