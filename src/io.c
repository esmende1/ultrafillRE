#include "io.h"


void io_init(uint8_t port, uint8_t pin_num, io_direction_t direction, io_selection_t selection)
{
    volatile uint8_t *dir_reg;
    volatile uint8_t *sel_reg;
    switch (port)
    {
    case 1:
        dir_reg = &P1DIR;
        sel_reg = &P1SEL;
        break;
    case 2:
        dir_reg = &P2DIR;
        sel_reg = &P2SEL;
        break;
    case 3:
        dir_reg = &P3DIR;
        sel_reg = &P3SEL;
        break;
    case 4:
        dir_reg = &P4DIR;
        sel_reg = &P4SEL;
        break;
    case 5:
        dir_reg = &P5DIR;
        sel_reg = &P5SEL;
        break;
    case 6:
        dir_reg = &P6DIR;
        sel_reg = &P6SEL;
        break;
    default:
        return; // Invalid port
    }
    if (direction == IO_OUTPUT)
    {
        *dir_reg |= 1 << pin_num; // Set the pin as output
    }
    else
    {
        *dir_reg &= ~(1 << pin_num); // Set the pin as input
    }
    if (selection == IO_PERIPHERAL)
    {
        *sel_reg |= 1 << pin_num; // Set the pin for peripheral function
    }
    else
    {
        *sel_reg &= ~(1 << pin_num); // Set the pin for GPIO function
    }
}

void io_set(uint8_t port, uint8_t pin_num, uint8_t state)
{
    volatile uint8_t *reg;
    switch (port)
    {
    case 1:
        reg = &P1OUT;
        break;
    case 2:
        reg = &P2OUT;
        break;
    case 3:
        reg = &P3OUT;
        break;
    case 4:
        reg = &P4OUT;
        break;
    case 5:
        reg = &P5OUT;
        break;
    case 6:
        reg = &P6OUT;
        break;
    default:
        return; // Invalid port
    }
    if (state)
    {
        *reg |= 1 << pin_num; // Set the pin
    }
    else
    {
        *reg &= ~(1 << pin_num); // Clear the pin
    }
}

void io_toggle(uint8_t port, uint8_t pin_num)
{
    volatile uint8_t *reg;
    switch (port)
    {
    case 1:
        reg = &P1OUT;
        break;
    case 2:
        reg = &P2OUT;
        break;
    case 3:
        reg = &P3OUT;
        break;
    case 4:
        reg = &P4OUT;
        break;
    case 5:
        reg = &P5OUT;
        break;
    case 6:
        reg = &P6OUT;
        break;
    default:
        return; // Invalid port
    }
    *reg ^= 1 << pin_num; // Toggle the pin
}