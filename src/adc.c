#include "adc.h"
#include "timer.h"
#include <stdio.h>

//Initialising PA4 as ADCIN4
void AdcInit(void)
{
    /**** configure GPIO pin for ADC ****/
    /* enable clock access to GPIOA */
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

    /* set single conversion mode */
    //ADC1->CFGR1 &= ~(ADC_CFGR1_CONT);

    /* set sequential channel */
  //  ADC1->CHSELR |= ADC_CHSELR_CHSEL4;

    /* select channel 18 - the internal temperature sensor (ADC_IN18) */
    ADC1->CHSELR |= ADC_CHSELR_CHSEL18;

    /* set the ADC clock (10 = PCLK/4 synchronous clock mode) */
    ADC1->CFGR2 |= (2U << ADC_CFGR2_CKMODE_Pos);
}

void AdcActivate(void)
{
    /* start the ADC calibration */
    ADC1->CR |=  ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL) {}   // wait for cal to finish

    /* enable the ADC */
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY)) {}  // wait until ADC is ready
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
    while(!(ADC1->ISR & ADC_ISR_EOC)) {}

    /* read result */
    return (ADC1->DR);
}


/* the temperature sensor is internally connected to the ADC_IN18
 * input channel  which is used to convert the sensor's output voltage to
 * a digital value.
 */
void TemperatureSensorInit(void)
{
    /* This bit is set and cleared by
     * software to enable/disable the temperature sensor. */
    ADC1_COMMON->CCR |= ADC_CCR_TSEN;
    ADC1_COMMON->CCR |= ADC_CCR_VREFEN;

    /* to be analysed later: */
    /* rising edge */
   // ADC1->CFGR1 |= (ADC_CFGR1_EXTEN_1);
   // ADC1->CFGR1 &= ~(ADC_CFGR1_EXTEN_0);

    /* trigger: TIM2 */
   // ADC1->CFGR1 &= ~(ADC_CFGR1_EXTSEL_0);
//ADC1->CFGR1 |= ADC_CFGR1_EXTSEL_1;
  //  ADC1->CFGR1 &= ~(ADC_CFGR1_EXTSEL_2);
}

double ReadChipTemperature(void)
{
    // Factory calibration values (from STM32L031 datasheet)
    // TS_CAL1: raw ADC at 30°C, VDDA=3.0V — address 0x1FF8007A
    // TS_CAL2: raw ADC at 130°C, VDDA=3.0V — address 0x1FF8007E
    uint16_t TS_CAL1 = *((uint16_t*)0x1FF8007A);
    uint16_t TS_CAL2 = *((uint16_t*)0x1FF8007E);
    //printf("CAL1=%u CAL2=%u\r\n", TS_CAL1, TS_CAL2);

    while (!(ADC1->ISR & ADC_ISR_EOC)) {}
    uint32_t data = ADC1->DR;

    // Scale raw reading to 3.0V reference
    uint32_t data_scaled = (uint32_t)((double)data * 3300.0 / 3000.0);
    double temperature = (double)((int32_t)data_scaled - (int32_t)TS_CAL1) * (130.0 - 30.0)
                         / (double)((int32_t)TS_CAL2 - (int32_t)TS_CAL1)
                         + 30.0;

    return temperature;
}