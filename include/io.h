#pragma once
#include <stdint.h>
#include "project_config.h"

typedef enum
{
    IO_INPUT = 0,
    IO_OUTPUT = 1
} io_direction_t;

typedef enum
{
    IO_GPIO = 0,
    IO_PERIPHERAL = 1
} io_selection_t;

void io_init(uint8_t port, uint8_t pin_num, io_direction_t direction, io_selection_t selection);
uint8_t io_read(uint8_t port, uint8_t pin_num);
void io_set(uint8_t port, uint8_t pin_num, uint8_t state);
void io_toggle(uint8_t port, uint8_t pin_num);