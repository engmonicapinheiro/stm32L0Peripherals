#include "systick.h"

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