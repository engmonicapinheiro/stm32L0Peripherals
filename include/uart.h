#ifndef __UART_H
#define __UART_H

#include "stm32l031xx.h"

#define SYS_FREQ   (2097000)  // MSI frequency, no prescaler (system clock, 2MHz)
#define APB1_CLK   (SYS_FREQ)
#define UART_BAUDRATE (115200)


void UartInit(void);
void UartWrite(int ch);
char UartRead(void);

#endif //UART_H