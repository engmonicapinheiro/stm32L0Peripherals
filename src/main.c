#include "stm32l031xx.h"
#include "gpio.h"

int main()
{
    GPIO_Init();

    while(1)
    {
        //reading the button
        if(GPIOB->IDR & GPIO_IDR_ID7)
        {
            GPIOB->ODR |= (GPIO_ODR_OD3);
        }
        else
        {
            GPIOB->ODR &= ~(GPIO_ODR_OD3);
        }

    }
}
