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
	__bis_SR_register(GIE); //Global interrupt enable
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
            for (uint8_t i = 0; i < 8; i++) {
                adc1_results[i] = adc_read(i);
            }

            ultrafill_process();
        }
    }

    return 0;
}
