#include "FM25CL64.h"

void FM25CL64_Configuration(){
    GPIO_InitTypeDef  gpio;
    SPI_InitTypeDef   spi;
    
    //时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    
    //引脚复用设置
    GPIO_PinAFConfig(GPIOB, GPIO_Pin_8,  GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_Pin_9,  GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_Pin_14, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_Pin_15, GPIO_AF_SPI2);
    
    
    gpio.GPIO_Pin                        =   GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15;
    gpio.GPIO_Mode                       =   GPIO_Mode_AF;
    gpio.GPIO_Speed                      =   GPIO_Speed_50MHz;
    gpio.GPIO_PuPd                       =   GPIO_PuPd_NOPULL;
    gpio.GPIO_OType                      =   GPIO_OType_PP;
    GPIO_Init(GPIOB, &gpio);
    
    //CS引脚输出高电平
    GPIOB->BSRRH = GPIO_Pin_9;
    
    //选用spi模式0
    spi.SPI_CPHA = SPI_CPHA_1Edge;
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    spi.SPI_NSS = SPI_NSS_Soft;
    spi.SPI_Mode = SPI_Mode_Master;
    spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线双向全双工
    spi.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输从 MSB 位开始
    spi.SPI_CRCPolynomial = 7; //CRC 值计算的多项式
    spi.SPI_DataSize = SPI_DataSize_8b; // SPI 发送接收8bit数据
    SPI_Init(SPI2, &spi);
    
}

