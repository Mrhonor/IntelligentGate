#ifndef __LCD1602__
#define __LCD1602__

#include "main.h"

void LCD1602_Init(void);
void LCD1602_Write(unsigned char cmd, char IsData);

#endif