#ifndef __PCF8563__
#define __PCF8563__

#include "main.h"
#define PCF8563_WRITE_ADD 0xA2
#define PCF8563_READ_ADD  0xA3

void PCFInit(void);
void IICWriteData(unsigned char SlaveAdd, unsigned char Add, unsigned char Data);
char IICWriteAndReadData(unsigned char SlaveWriteAdd, unsigned char Add, unsigned char SlaveReadAdd);

char WaitForAcknowledgement(void);

void StartIIC(void);
void StopIIC(void);
void SendBit(char bitValue);

char BCDtoData(unsigned char Data);

#endif