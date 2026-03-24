#ifndef __ADC_H
#define __ADC_H
#include "stm32l031xx.h"
#include <stdint.h>

void AdcInit(void);
void AdcActivate(void);
void AdcStartConversion(void);
uint32_t AdcRead(void);

#endif   //ADC_H