#include "timer.h"
#include "gpio.h"
#include "stdio.h"

static void Timer2Callback(void);

void Timer1HzInit(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    /* prescaler calculated according to the sysclock of 2097000 Hz */
    TIM2->PSC = 2097 - 1;
    /* autoreload */
    TIM2->ARR = 1000 - 1;
    /* clear the timer counter */
    TIM2->CNT = 0;
    /* enable the timer */
    TIM2->CR1 |= TIM_CR1_CEN;
}

void TimerDelayOneSecond()
{
    /* wait for UIF to be set */
    while(!(TIM2->SR & TIM_SR_UIF));
    /* clear the flag UIF */
    TIM2->SR &= ~(TIM_SR_UIF);
}

/** timer interrupt functions **/

void Timer1HzInterruptInit(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    /* prescaler calculated according to the sysclock of 2097000 Hz */
    TIM2->PSC = 2097 - 1;
    /* autoreload */
    TIM2->ARR = 1000 - 1;
    /* clear the timer counter */
    TIM2->CNT = 0;
    /* enable the timer */
    TIM2->CR1 |= TIM_CR1_CEN;

    /* enable TIM interrupt */
    TIM2->DIER |= TIM_DIER_UIE;
    /* enable interrupt in NVIC */
    NVIC_EnableIRQ(TIM2_IRQn);
}

static void Timer2Callback(void)
{
    printf("One second ... \n\r");
    ToggleGreenLed();
}

void TIM2_IRQHandler(void)
{
    /* clear update interrupt flag */
    TIM2->SR &= ~ (TIM_SR_UIF);

    /* do something... */
    Timer2Callback();
}