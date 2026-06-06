#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>

void GPIO_Init(void);
void ToggleGreenLedPseudoDelay(void);
void ToggleGreenLed(void);
uint8_t GetButtonState(void);

#endif //__GPIO_H