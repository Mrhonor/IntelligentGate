#include "PCF8563.h"

void PCF8563_Configuration(){
    GPIO_InitTypeDef  gpio;
    I2C_InitTypeDef   iic;
    
    //ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,   ENABLE);
    
    //����SCL����
    gpio.GPIO_Pin              =   GPIO_Pin_6;
    gpio.GPIO_Mode             =   GPIO_Mode_AF;
    gpio.GPIO_Speed            =   GPIO_Speed_50MHz;
    gpio.GPIO_PuPd             =   GPIO_PuPd_NOPULL;
    gpio.GPIO_OType            =   GPIO_OType_OD;  //����Ϊ��©ģʽ
    GPIO_Init(GPIOB, &gpio);
    
    
    //�������ŵ�IIC1_SCL
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);

    //����SDA����
    gpio.GPIO_Pin              =   GPIO_Pin_7;
    GPIO_Init(GPIOB, &gpio);
    
    //�������ŵ�IIC1_SCL
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

    iic.I2C_Mode                = I2C_Mode_I2C;
    iic.I2C_Ack                 = I2C_Ack_Enable;
    iic.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;  //PCF8563Ϊ7BitѰ��ģʽ
    iic.I2C_DutyCycle           = I2C_DutyCycle_2;        // PCF8563�͵�ƽ1.3��s���ߵ�ƽʱ��0.6��s������2��1ģʽ
    iic.I2C_ClockSpeed          = 400000;                 // 400kHz
    iic.I2C_OwnAddress1         = 0x0A;                   // �����ַ
    I2C_Init(I2C1, &iic);
    I2C_Cmd(I2C1, ENABLE);
}

