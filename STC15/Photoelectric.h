#ifndef __PHOTOELECTRIC__
#define __PHOTOELECTRIC__
#include "main.h"

// 门的开关状态 0表示关闭 1表示开启
extern char DoorOpenStatus;
extern char DoorOpenTime;

void Photoelectric_Init(void);
void INT0_interrupt(void);

#endif