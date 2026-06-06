#include "gpio.h"
#include "stm32l031xx.h"

//LED: PB3, PA8
//Button: D4 -> PB7
void GPIO_Init(void)
{
    /* enable clock access */
    RCC->IOPENR |= RCC_IOPENR_IOPAEN;
    RCC->IOPENR |= RCC_IOPENR_IOPBEN;

    /* set PB3 as output pin */
    GPIOB->MODER |= GPIO_MODER_MODE3_0;
    GPIOB->MODER &= ~(GPIO_MODER_MODE3_1);

    /*set PA8 as output */
    GPIOA->MODER |= GPIO_MODER_MODE8_0;
    GPIOA->MODER &= ~(GPIO_MODER_MODE8_1);

    /* set PB7 as input */
    GPIOB->MODER &= ~(GPIO_MODER_MODE7_0);
    GPIOB->MODER &= ~(GPIO_MODER_MODE7_1);
}

void ToggleGreenLedPseudoDelay(void)
{
    GPIOA->BSRR |= GPIO_BSRR_BS_8;
    for(int i = 0; i < 1000; ++i);
    GPIOA->BSRR |= GPIO_BSRR_BR_8;
    for(int i = 0; i < 10000; ++i);
}

void ToggleGreenLed(void)
{
    GPIOA->ODR ^= GPIO_ODR_OD8;
}

uint8_t GetButtonState(void)
{
    return (GPIOB->IDR & GPIO_IDR_ID7);
}