#include "FM25CL64.h"

void FM25CL64_Configuration(){
    GPIO_InitTypeDef  gpio;
    SPI_InitTypeDef   spi;
    
    //ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    
    //���Ÿ�������
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
    
    //CS��������ߵ�ƽ
    GPIOB->BSRRH = GPIO_Pin_9;
    
    //ѡ��spiģʽ0
    spi.SPI_CPHA = SPI_CPHA_1Edge;
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    spi.SPI_NSS = SPI_NSS_Soft;
    spi.SPI_Mode = SPI_Mode_Master;
    spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //˫��˫��ȫ˫��
    spi.SPI_FirstBit = SPI_FirstBit_MSB; //���ݴ���� MSB λ��ʼ
    spi.SPI_CRCPolynomial = 7; //CRC ֵ����Ķ���ʽ
    spi.SPI_DataSize = SPI_DataSize_8b; // SPI ���ͽ���8bit����
    SPI_Init(SPI2, &spi);
    
}

