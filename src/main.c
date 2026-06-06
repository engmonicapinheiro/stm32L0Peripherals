#include "stm32l031xx.h"
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"
#include "exti.h"
#include "adxl345.h"

float xg, yg, zg;
int16_t x, y, z;
uint8_t acc_data[6];


int main()
{
    GPIO_Init();
    UartInit();
    AdxlInit();

    printf("Hello from STM32L0......\n\r");

    while(1)
    {
        printf("running a new test......\n\r");

        AdxlRead(DATA_START_ADDR, acc_data);
        /* combine x0 and x1 data */
        x = ((acc_data[1] << 8) | acc_data[0]);
        y = ((acc_data[3] << 8) | acc_data[2]);
        z = ((acc_data[5] << 8) | acc_data[4]);

        xg = x * 0.0078;
        yg = y * 0.0078;
        zg = z * 0.0078;
    }
}
