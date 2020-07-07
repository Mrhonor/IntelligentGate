#ifndef __FM25CL64__
#define __FM25CL64__

#include "main.h"

void FM25CL64_Init(void);

void SPIWriteData(unsigned char Data, unsigned int add);
unsigned char SPIReadData(unsigned int add);

void SendData(unsigned char Data);
unsigned char ReadData(void);
#endif
