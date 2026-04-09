#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32l031xx.h"

#define SYSTICK_LOAD_VAL   2097
#define ONE_SECOND_LOAD    2097000

void Systick_delay_ms(int delay);
void Systick1HzInterrupt(void);

#endif //__SYSTICK_H