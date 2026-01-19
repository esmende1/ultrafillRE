#include "project_config.h"
#include <stdint.h>
#include "io.h"
#include "io_ultrafill.h"


void init(void) {
    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer}
}

void delay_nop(uint32_t count) {
    while(count--) {
        __no_operation();
    }
}

void adc_init_ultrafill(void) {

    adc_setup_channel(PRESSURE_IN_LP);
}

int main(void) {
    init();
    io_init_ultrafill();

    adc_init();
    adc_init_ultrafill();

    while(1) {
        for (uint8_t level = 0; level <= 4; level++) {
            blue_led_set_level(level);
            delay_nop(100000);
        }
    }
    
    return 0;
}
