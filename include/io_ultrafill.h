#pragma once
#include <stdint.h>
#include "project_config.h"


#define LED_GREEN 2, 0
#define LED_AMBER 2, 1
#define LED_RED 2, 3
#define LED_BLUE1 1, 2
#define LED_BLUE2 1, 3
#define LED_BLUE3 1, 4
#define LED_BLUE4 1, 5
#define COMPRESSOR_ENABLE 4, 4

#define BUTTON_INPUT 5, 6

#define PRESSURE_IN_HP 6, 3

//Not sure about this one
#define PRESSURE_IN_LP 6, 1

#define PRESSURE_HP_ADC_CHANNEL 0
#define PRESSURE_LP_ADC_CHANNEL 1

void io_init_ultrafill(void);

void blue_led_set_level(uint8_t level);