#include "main.h"

int main(void)
{
    USART1_Configuration();
    KeyBoard_Configuration();
    LCD1602_Configuration();
    Photoelectric_Configuration();
    Buzzer_Configuration();
    FM25CL64_Configuration();
    DHT11_Configuration();
    PCF8563_Configuration();
    
    
    
    while (1)
    {

    }
}
