#pragma once

#include <stdint.h>
#include <project_config.h>

void adc_init(void);
void adc_setup_channel(uint8_t port_num, uint8_t pin_num, uint8_t chan_num, uint8_t is_last);
void adc_start(void);
uint16_t adc_read(uint8_t channel);