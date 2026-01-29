#pragma once 

#include "project_config.h"


inline static void clock_init(void)
{
    __bis_SR_register(OSCOFF);

    IFG1 &= ~OFIFG; // Clear OSC fault flag

    do {
        __no_operation();
    } while (IFG1 & OFIFG); // Test oscillator fault flag

    BCSCTL2 |= SELM_2 | SELS | DIVS_3; // MCLK=XT2CLK, SMCLK=XT2CLK/4
}