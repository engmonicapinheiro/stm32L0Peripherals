#include "stm32l031xx.h"
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"


int main()
{
    GPIO_Init();
    UartInit();
    AdcInit();
    AdcActivate();
    AdcStartConversion();
    Timer1HzInit();

    printf("Hello from STM32L0......\n\r");

    while(1)
    {
        TimerDelayOneSecond();
        printf("A second just passed!\r\n");
        ToggleGreenLed();
    }
}
