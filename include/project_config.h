#pragma once

#include <msp430f155.h>

#define CPU_FREQ_HZ 3686000 // ~3.686 MHz
#define SMCLK_FREQ_HZ (CPU_FREQ_HZ / 8) // ~500 kHz

#define SYSTEM_TICK_MS 100
