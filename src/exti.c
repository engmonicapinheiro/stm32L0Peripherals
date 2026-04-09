#include "exti.h"
#include "gpio.h"
#include "stdio.h"

//Button: D4 -> PB7
void ExtiInit(void)
{
    /* enable clock access to GPIOB */
    RCC->IOPENR |= RCC_IOPENR_IOPBEN;

    /* enable clock access to SYSCFG */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* set PB7 as input pin */
    GPIOB->MODER &= ~(GPIO_MODER_MODE7_0);
    GPIOB->MODER &= ~(GPIO_MODER_MODE7_1);

    /* clear port selection for EXTI7
     * SYSCFG->EXTICR[1] forEXTICR2 register
     * PB is 0001
     * clear bits 12, 13, 14 and 15 */
    SYSCFG->EXTICR[1] &= ~(1U << 12);
    SYSCFG->EXTICR[1] &= ~(1U << 13);
    SYSCFG->EXTICR[1] &= ~(1U << 14);
    SYSCFG->EXTICR[1] &= ~(1U << 15);

    /* select PORTB for EXTI7 (PB is 0001) */
    SYSCFG->EXTICR[1] |= (1U << SYSCFG_EXTICR2_EXTI7_Pos);

    /* unmask EXTI7 */
    EXTI->IMR |= EXTI_EMR_EM7;

    /* select falling edge trigger */
    EXTI->FTSR |= EXTI_FTSR_FT7;

    /* enable EXTI line in NVIC */
    NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void EXTI4_15_IRQHandler(void)
{
    if((EXTI->PR & EXTI_PR_PIF7) != 0)
    {
        /* clear PR flag */
        EXTI->PR |= EXTI_PR_PIF7;

        /* do something... */
        ToggleGreenLed();
        printf("button pressed! \n\r");
    }
}