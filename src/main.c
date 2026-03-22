#include "stm32l031xx.h"
#include <stdio.h>
#include "gpio.h"
#include "uart.h"


char key;

int main()
{
    GPIO_Init();
    UartInit();

    printf("Hello from STM32L0......\n\r");

    while(1)
    {
        key = UartRead();
        if(key == '1')
        {
            GPIOA->BSRR |= GPIO_BSRR_BS_8;
        }
        else
        {
            GPIOA->BSRR |= GPIO_BSRR_BR_8;
        }

        //UartWrite('Y');
    }
}
