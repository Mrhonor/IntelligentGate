#ifndef __BUZZER__
#define __BUZZER__
#include "main.h"

void Buzzer_Init(void);

void RingTheBuzzer(unsigned int ms);
void TIM0_interrupt(void);
#endif