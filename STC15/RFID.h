#ifndef __RFID__
#define __RFID__

#include "main.h"

void RFID_Init();
void Uart1_Init();
void UART1_interrupt();
void RFID_Check(char * msg);

#endif