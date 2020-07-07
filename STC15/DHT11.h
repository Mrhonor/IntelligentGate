#ifndef __DHT11__
#define __DHT11__

#include "main.h"

extern float Temperature;
extern float Humidity;

void DHT11_Init(void);
void GetDHTData(void);
void Unpack(void);

#endif
