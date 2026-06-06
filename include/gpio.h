#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>
#include <stdbool.h>

void GPIO_Init(void);
void ToggleGreenLedPseudoDelay(void);
void ToggleGreenLed(void);
bool GetButtonState(void);

#endif //__GPIO_H