#ifndef __KEYBOARD__
#define __KEYBOARD__
#include "main.h"

extern volatile char KeyBoardCheckFlag;
extern int SleepTime;


void KeyBoard_Init(void);
void INT1_interrupt(void);
void SleepTimeReset(void);
void Sleep(void);
char IsAnyKeyPress(void);
void PasswordCheck(char* Password, char num);

#endif