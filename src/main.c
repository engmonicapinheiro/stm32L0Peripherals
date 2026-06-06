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
        buttonState = GetButtonState();
        sensorValue = AdcRead();
        printf("%d\r\n", sensorValue);
        Systick_delay_ms(500);

    }
}
