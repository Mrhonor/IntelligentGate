#ifndef __PHOTOELECTRIC__
#define __PHOTOELECTRIC__
#include "main.h"

// �ŵĿ���״̬ 0��ʾ�ر� 1��ʾ����
extern char DoorOpenStatus;
extern char DoorOpenTime;

void Photoelectric_Init(void);
void INT0_interrupt(void);

#endif