#pragma once

#include <project_config.h>



void adc_init(void);
void adc_setup_channel(uint8_t channel);
void adc_start(void);
uint16_t adc_read(uint8_t channel);