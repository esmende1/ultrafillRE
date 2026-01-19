#pragma once
#include "project_config.h"

#define LED_D19_GREEN1 2, 0
#define LED_D10_AMBER1 2, 1
#define LED_D3_RED1 2, 3
#define LED_D8_BLUE1 1, 2
#define LED_D8_BLUE2 1, 3
#define LED_D8_BLUE3 1, 4
#define LED_D8_BLUE4 1, 5

//Not sure about these
#define PRESSURE_IN_LP 6, 0
#define PRESSURE_IN_HP 6, 1

void io_init_ultrafill(void);

void blue_led_set_level(uint8_t level);