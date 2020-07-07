#ifndef __MAIN__
#define __MAIN__

#include <STC15F2K60S2.H>

#include "RFID.h"
#include "KeyBoard.h"
#include "LCD1602.h"
#include "PCF8563.h"
#include "Photoelectric.h"
#include "Buzzer.h"
#include "FM25CL64.h"
#include "DHT11.h"

#define     MAIN_Fosc       11059200L

void delay(int time);
void delay_ms(unsigned char ms);
void delay_us(unsigned char us);
char abs(char num);
#endif