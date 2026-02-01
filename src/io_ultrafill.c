#include "io_ultrafill.h"
#include "io.h"
void io_init_ultrafill(void) {
    
    io_init(LED_GREEN, IO_OUTPUT, IO_GPIO); 
    io_init(LED_AMBER, IO_OUTPUT, IO_GPIO); 
    io_init(LED_RED, IO_OUTPUT, IO_GPIO); 
    io_init(LED_BLUE1, IO_OUTPUT, IO_GPIO); 
    io_init(LED_BLUE2, IO_OUTPUT, IO_GPIO);
    io_init(LED_BLUE3, IO_OUTPUT, IO_GPIO); 
    io_init(LED_BLUE4, IO_OUTPUT, IO_GPIO); 
    io_init(PRESSURE_IN_LP, IO_INPUT, IO_PERIPHERAL);
        io_set(LED_GREEN, 1);
    io_init(PRESSURE_IN_HP, IO_INPUT, IO_PERIPHERAL); 
    io_init(COMPRESSOR_ENABLE, IO_OUTPUT, IO_GPIO);
    io_init(6, 0, IO_INPUT, IO_PERIPHERAL);
    io_init(6, 2, IO_INPUT, IO_PERIPHERAL); 
    io_init(6, 4, IO_INPUT, IO_PERIPHERAL); 
    io_init(6, 5, IO_INPUT, IO_PERIPHERAL);
    io_init(6, 6, IO_INPUT, IO_PERIPHERAL); 
    io_init(6, 7, IO_INPUT, IO_PERIPHERAL); 

    io_set(LED_GREEN, 0); // Turn off LED_D19_GREEN1
    io_set(LED_AMBER, 0); // Turn off LED_D10_AMBER1
    io_set(LED_RED, 0); // Turn off LED_D3_RED1
    io_set(LED_BLUE1, 0); // Turn off LED_D8_BLUE1
    io_set(LED_BLUE2, 0); // Turn off LED_D8_BLUE2
    io_set(LED_BLUE3, 0); // Turn off LED_D8_BLUE3
    io_set(LED_BLUE4, 0); // Turn off LED_D8_BLUE4
    io_set(COMPRESSOR_ENABLE, 0); // Turn off COMPRESSOR_ENABLE

}


void blue_led_set_level(uint8_t level) {
    switch (level) {
        case 0:
            io_set(LED_BLUE1, 0);
            io_set(LED_BLUE2, 0);
            io_set(LED_BLUE3, 0);
            io_set(LED_BLUE4, 0);
            break;
        case 1:
            io_set(LED_BLUE1, 1);
            io_set(LED_BLUE2, 0);
            io_set(LED_BLUE3, 0);
            io_set(LED_BLUE4, 0);
            break;
        case 2:
            io_set(LED_BLUE1, 0);
            io_set(LED_BLUE2, 1);
            io_set(LED_BLUE3, 0);
            io_set(LED_BLUE4, 0);
            break;
        case 3:
            io_set(LED_BLUE1, 0);
            io_set(LED_BLUE2, 0);
            io_set(LED_BLUE3, 1);
            io_set(LED_BLUE4, 0);
            break;
        case 4:
            io_set(LED_BLUE1, 0);
            io_set(LED_BLUE2, 0);
            io_set(LED_BLUE3, 0);
            io_set(LED_BLUE4, 1);
            break;
        default:
            io_set(LED_BLUE1, 0);
            io_set(LED_BLUE2, 0);
            io_set(LED_BLUE3, 0);
            io_set(LED_BLUE4, 0);
            break;
    }
}