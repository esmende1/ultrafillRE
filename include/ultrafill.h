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
    ULTRAFILL_FAULT_HP_SENSOR = 8,
    ULTRAFILL_FAULT_FAN_FAILURE = 16
} ultrafill_fault_t;

#define ULTRAFILL_MAX_FILL_PRESSURE_PSI 3100


//Number of fault counts before trying to start again.
//This keeps us from doing rapid retries during over/under pressure conditions.
#define ULTRAFILL_FAULT_RETRY_COUNTS 50

//HP Sensor is about 780 counts per volt, ADC at 5V reads aprox 3900
//HP sensor is 1-5V 3500psi sensor 780 counts = 0psi, 3900 counts = 3500psi
//S aprox 890 counts per 1000psi
#define ULTRAFILL_HP_ZERO_PSI_ADC_COUNTS 780
#define ULTRAFILL_HP_ADC_COUNTS_1000PSI 890
#define ULTRAFILL_HP_FULL_ADC_COUNTS ULTRAFILL_HP_ZERO_PSI_ADC_COUNTS + (ULTRAFILL_MAX_FILL_PRESSURE_PSI / 1000) * ULTRAFILL_HP_ADC_COUNTS_1000PSI
#define ULTRAFILL_HP_OVERPRESSURE_ADC_COUNTS 3700
#define ULTRAFILL_HP_SENSORFAULT_ADC_COUNTS 700

#define ULTRAFILL_LP_UNDERPRESSURE_ADC_COUNTS 1200
#define ULTRAFILL_LP_OVERPRESSURE_ADC_COUNTS 3500


uint16_t ultrafill_read_lp_pressure(void);
uint16_t ultrafill_read_hp_pressure(void);
ultrafill_fault_t ultrafill_check_system(void);
void ultrafill_init(void);
void ultrafill_process(void);
void ultrafill_start_filling(void);
void ultrafill_stop_filling(void);
void ultrafill_update_leds(void);   