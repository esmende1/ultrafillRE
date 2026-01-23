#include "project_config.h"
#include <stdint.h>
#include "io.h"
#include "io_ultrafill.h"
#include "adc.h"


void init(void) {
    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer}
}

void delay_nop(uint32_t count) {
    while(count--) {
        __no_operation();
    }
}

void adc_init_ultrafill(void) 
{
    adc_setup_channel(PRESSURE_IN_LP,0,0);
    adc_setup_channel(PRESSURE_IN_HP,1,1); // Last channel needs is_last = 1
}
volatile uint16_t adc1_results[8] = {0};

int main(void) {
    init();
    io_init_ultrafill();

    adc_init();
    adc_init_ultrafill();
    adc_start();

    while(1) {
        for (uint8_t chan = 0; chan < 8; chan++) 
        {
                adc1_results[chan] = adc_read(chan);
        }

        blue_led_set_level(adc1_results[0] / 700);
        delay_nop(10000);

    }
    
    return 0;
}
