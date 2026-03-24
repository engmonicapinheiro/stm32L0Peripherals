#include "stm32l031xx.h"
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "adc.h"


uint32_t sensorValue;

int main()
{
    GPIO_Init();
    UartInit();
    AdcInit();
    AdcActivate();
    AdcStartConversion();

    printf("Hello from STM32L0......\n\r");

    while(1)
    {
        sensorValue = AdcRead();
        printf("%ld\n\r", sensorValue);
    }
}
