#include "stm32l031xx.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"
#include "exti.h"
#include "../include/adc.h"


bool buttonState;
double chipTemperature;

int main()
{
    GPIO_Init();
    UartInit();
    AdcInit();
    TemperatureSensorInit();
    AdcActivate();
    AdcStartConversion();

    printf("Hello from STM32L0......\n\r");

    while(1)
    {
        chipTemperature = ReadChipTemperature();
        printf("%g\r\n", chipTemperature);
        Systick_delay_ms(500);

    }
}
