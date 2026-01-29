
#include <stdint.h>
#include "io.h"
#include "io_ultrafill.h"
#include "timer.h"


volatile uint8_t timer_tick = 0;
void timer_init(void)
{
    TACTL = TASSEL_2 | ID_3 | MC_1;
    TACCR0 = (((SMCLK_FREQ_HZ / 8) / 1000) * SYSTEM_TICK_MS) - 1;
    TACCTL0 |= CCIE;  // Enable CCR0 interrupt
    TACTL &= ~TAIFG;
    timer_tick = 0;
}


__attribute__((interrupt(TIMERA0_VECTOR)))
void Timer_A_ISR(void)
{
    timer_tick = 1;
}

uint8_t timer_system_tick(void)
{
    uint8_t temp = timer_tick;
    timer_tick = 0;
    return temp;
}