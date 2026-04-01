#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32l031xx.h"

#define SYSTICK_LOAD_VAL   2097

void Systick_delay_ms(int delay);


#endif //__SYSTICK_H