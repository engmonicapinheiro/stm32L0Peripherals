#include "systick.h"
#include "gpio.h"
#include "uart.h"
#include "stdio.h"


static void SystickCallback(void);


void Systick_delay_ms(int delay)
{
    /* reload with number of clocks per milliseconds */
    SysTick->LOAD = SYSTICK_LOAD_VAL;

    /* clear the current value register */
    SysTick->VAL = 0;

    /*select the clock source and enable the timer */
    SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

    for(int i = 0; i < delay; ++i)
    {
        /* wait until COUNTFLAG is set */
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    }

    /* disable systick */
    SysTick->CTRL = 0;
}

/** systick interrupt functions **/

void Systick1HzInterrupt(void)
{
    /* reload with number of clocks per milliseconds */
    SysTick->LOAD = ONE_SECOND_LOAD;

    /* clear the current value register */
    SysTick->VAL = 0;

    /*select the clock source, enable systick interrupt and enable the timer */
    SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk);
}

/* callback function */
static void SystickCallback(void)
{
    ToggleGreenLed();
    printf("A second just passed! \n\r");
}

void SysTick_Handler(void)
{
    //do something
    SystickCallback();
}
