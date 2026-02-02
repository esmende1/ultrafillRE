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

volatile uint8_t io_regs[6];

void adc_init_ultrafill(void)
{

    adc_setup_channel(PRESSURE_IN_LP, PRESSURE_LP_ADC_CHANNEL, 0); // Last channel needs is_last = 1
    adc_setup_channel(6, 1, 1, 0);
    adc_setup_channel(6, 1, 2, 0);
    adc_setup_channel(PRESSURE_IN_HP, PRESSURE_HP_ADC_CHANNEL, 0);
    adc_setup_channel(6, 4, 4, 0);
    adc_setup_channel(6, 5, 5, 0);
    adc_setup_channel(6, 6, 6, 0);
    adc_setup_channel(6, 7, 7, 1);
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
            io_regs[0] = P1IN;
            io_regs[1] = P2IN;
            io_regs[2] = P3IN;
            io_regs[3] = P4IN;
            io_regs[4] = P5IN;
            io_regs[5] = P6IN;
            for (uint8_t i = 0; i < 8; i++) {
                adc1_results[i] = adc_read(i);
            }

            ultrafill_process();
        }
    }

    return 0;
}
