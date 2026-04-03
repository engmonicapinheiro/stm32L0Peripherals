#include "timer.h"

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