#include "adc.h"


//Initialising PA4 as ADCIN4
void AdcInit(void)
{
    /**** configure GPIO pin for ADC ****/
    /* enable clocl access to GPIOA */
      RCC->IOPENR |= RCC_IOPENR_IOPAEN;

    /* set PA4 mode to analog mode */
    GPIOA->MODER |= GPIO_MODER_MODE4_0;
    GPIOA->MODER |= GPIO_MODER_MODE4_1;

    /**** Configure the ADC module ****/
    /* enable clock access to ADC */
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

    /* set the ADC sampling time to 160.5 ADC clock cycles (111 in the register) */
    ADC1->SMPR |= (7U << ADC_SMPR_SMP_Pos);

    /* set continuous conversion mode */
    ADC1->CFGR1 |= ADC_CFGR1_CONT;

    /* set sequential channel */
    ADC1->CHSELR |= ADC_CHSELR_CHSEL4;

    /* set the ADC clock (10 = PCLK/4 synchronous clock mode) */
    ADC1->CFGR2 |= (2U << ADC_CFGR2_CKMODE_Pos);
}

void AdcActivate(void)
{
    /* start the ADC calibration */
    ADC1->CR |=  ADC_CR_ADCAL;

    /* enable the ADC */
    ADC1->CR |= ADC_CR_ADEN;
}

void AdcStartConversion(void)
{
    /* start conversion */
    ADC1->CR |= ADC_CR_ADSTART;

    /* clear the end-of-conversion flag */
    ADC1->ISR &= ~(ADC_ISR_EOC);
}

uint32_t AdcRead(void)
{
    /* wait for conversion completion */
    while(!(ADC1->ISR & ADC_ISR_EOC));

    /* read result */
    return (ADC1->DR);
}