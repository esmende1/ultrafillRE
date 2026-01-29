#pragma once
#include <stdint.h>
#include "project_config.h"

typedef enum {
    ULTRAFILL_STATE_IDLE,
    ULTRAFILL_STATE_FILLING,
    ULTRAFILL_STATE_FULL,
    ULTRAFILL_STATE_FAULT
} ultrafill_state_t;

typedef enum {
    ULTRAFILL_FAULT_NONE = 0,
    ULTRAFILL_FAULT_LP_UNDERPRESSURE = 1,
    ULTRAFILL_FAULT_LP_OVERPRESSURE = 2,
    ULTRAFILL_FAULT_HP_OVERPRESSURE = 4,
    ULTRAFILL_FAULT_FAN_FAILURE = 8
} ultrafill_fault_t;

//Number of fault counts before trying to start again.
//This keeps us from doing rapid retries during over/under pressure conditions.
#define ULTRAFILL_FAULT_RETRY_COUNTS 50

//TODO put real values here
#define ULTRAFILL_HP_FULL_ADC_COUNTS 3100
#define ULTRAFILL_HP_FULL_ADC_COUNTS 3100
#define ULTRAFILL_HP_OVERPRESSURE_ADC_COUNTS 3300
#define ULTRAFILL_LP_UNDERPRESSURE_ADC_COUNTS 100
#define ULTRAFILL_LP_OVERPRESSURE_ADC_COUNTS 2000


uint16_t ultrafill_read_lp_pressure(void);
uint16_t ultrafill_read_hp_pressure(void);
ultrafill_fault_t ultrafill_check_system(void);
void ultrafill_init(void);
void ultrafill_state_machine(void);
void ultrafill_start_filling(void);
void ultrafill_stop_filling(void);
void ultrafill_update_leds(void);   