#ifndef __TIMER_h
#define __TIMER_h

#include "stm32l031xx.h"

void Timer1HzInit(void);
void TimerDelayOneSecond();
void Timer1HzInterruptInit(void);

#endif  //TIMER_H