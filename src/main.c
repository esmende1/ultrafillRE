#include "project_config.h"
#include <stdint.h>
#include "io.h"
#include "io_ultrafill.h"
#include "adc.h"
#include "timer.h"
#include "clock.h"
#include "ultrafill.h"

void init(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    clock_init();
    //Global interrupt enable
	__bis_SR_register(GIE);
}

void adc_init_ultrafill(void)
{
    adc_setup_channel(PRESSURE_IN_LP, 0, 0);
    adc_setup_channel(PRESSURE_IN_HP, 1, 1); // Last channel needs is_last = 1
}
volatile uint16_t adc1_results[8] = {0};

int main(void)
{
    init();
    io_init_ultrafill();

    adc_init();
    adc_init_ultrafill();
    adc_start();
    timer_init();
    ultrafill_init();

    while (1)
    {
        if (timer_system_tick())
        {
            ultrafill_state_machine();
        }
    }

    return 0;
}
