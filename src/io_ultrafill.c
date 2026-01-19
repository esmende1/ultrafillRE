#include "io_ultrafill.h"
#include "io.h"
void io_init_ultrafill(void) {
    
    io_init(LED_D19_GREEN1, IO_OUTPUT, IO_GPIO); 
    io_init(LED_D10_AMBER1, IO_OUTPUT, IO_GPIO); 
    io_init(LED_D3_RED1, IO_OUTPUT, IO_GPIO); 
    io_init(LED_D8_BLUE1, IO_OUTPUT, IO_GPIO); 
    io_init(LED_D8_BLUE2, IO_OUTPUT, IO_GPIO);
    io_init(LED_D8_BLUE3, IO_OUTPUT, IO_GPIO); 
    io_init(LED_D8_BLUE4, IO_OUTPUT, IO_GPIO); 
    io_init(PRESSURE_IN_LP, IO_INPUT, IO_PERIPHERAL);
    io_init(PRESSURE_IN_HP, IO_INPUT, IO_PERIPHERAL); 

    io_set(LED_D19_GREEN1, 0); // Turn off LED_D19_GREEN1
    io_set(LED_D10_AMBER1, 0); // Turn off LED_D10_AMBER1
    io_set(LED_D3_RED1, 0); // Turn off LED_D3_RED1
    io_set(LED_D8_BLUE1, 0); // Turn off LED_D8_BLUE1
    io_set(LED_D8_BLUE2, 0); // Turn off LED_D8_BLUE2
    io_set(LED_D8_BLUE3, 0); // Turn off LED_D8_BLUE3
    io_set(LED_D8_BLUE4, 0); // Turn off LED_D8_BLUE4

}


void blue_led_set_level(uint8_t level) {
    switch (level) {
        case 0:
            io_set(LED_D8_BLUE1, 0);
            io_set(LED_D8_BLUE2, 0);
            io_set(LED_D8_BLUE3, 0);
            io_set(LED_D8_BLUE4, 0);
            break;
        case 1:
            io_set(LED_D8_BLUE1, 1);
            io_set(LED_D8_BLUE2, 0);
            io_set(LED_D8_BLUE3, 0);
            io_set(LED_D8_BLUE4, 0);
            break;
        case 2:
            io_set(LED_D8_BLUE1, 0);
            io_set(LED_D8_BLUE2, 1);
            io_set(LED_D8_BLUE3, 0);
            io_set(LED_D8_BLUE4, 0);
            break;
        case 3:
            io_set(LED_D8_BLUE1, 0);
            io_set(LED_D8_BLUE2, 0);
            io_set(LED_D8_BLUE3, 1);
            io_set(LED_D8_BLUE4, 0);
            break;
        case 4:
            io_set(LED_D8_BLUE1, 0);
            io_set(LED_D8_BLUE2, 0);
            io_set(LED_D8_BLUE3, 0);
            io_set(LED_D8_BLUE4, 1);
            break;
        default:
            break;
    }
}