#include "ultrafill.h"
#include "adc.h"
#include "io.h"
#include "io_ultrafill.h"

ultrafill_state_t ultrafill_state;
uint16_t ultrafill_fault_count;
volatile ultrafill_fault_t ultrafill_current_fault;

uint16_t ultrafill_read_lp_pressure(void)
{
    return adc_read(PRESSURE_LP_ADC_CHANNEL);
}
uint16_t ultrafill_read_hp_pressure(void)
{
    return adc_read(PRESSURE_HP_ADC_CHANNEL);
}

ultrafill_fault_t ultrafill_check_system(void)
{

    ultrafill_fault_t fault = ULTRAFILL_FAULT_NONE;

    uint16_t lp_pressure = ultrafill_read_lp_pressure();
    uint16_t hp_pressure = ultrafill_read_hp_pressure();

    if (lp_pressure < ULTRAFILL_LP_UNDERPRESSURE_ADC_COUNTS)
    {
        fault |= ULTRAFILL_FAULT_LP_UNDERPRESSURE;
    }
    if (lp_pressure > ULTRAFILL_LP_OVERPRESSURE_ADC_COUNTS)
    {
        fault |= ULTRAFILL_FAULT_LP_OVERPRESSURE;
    }
    if (hp_pressure > ULTRAFILL_HP_OVERPRESSURE_ADC_COUNTS)
    {
        fault |= ULTRAFILL_FAULT_HP_OVERPRESSURE;
    }
    if (hp_pressure < ULTRAFILL_HP_SENSORFAULT_ADC_COUNTS)
    {
        fault |= ULTRAFILL_FAULT_HP_SENSOR;
    }
    // TODO FAN fault detection
    return fault;
}

void ultrafill_start_filling(void)
{
    io_set(COMPRESSOR_ENABLE, 1);
}

void ultrafill_stop_filling(void)
{
    io_set(COMPRESSOR_ENABLE, 0);
}

void ultrafill_init(void)
{
    ultrafill_state = ULTRAFILL_STATE_IDLE;
    ultrafill_fault_count = 0;
    ultrafill_current_fault = ULTRAFILL_FAULT_NONE;
}

void ultrafill_process(void)
{
    ultrafill_current_fault = ultrafill_check_system();

    if (ultrafill_current_fault != ULTRAFILL_FAULT_NONE)
    {
        ultrafill_stop_filling();
        ultrafill_state = ULTRAFILL_STATE_FAULT;
        ultrafill_fault_count = 0;
    }
    switch (ultrafill_state)
    {
    case ULTRAFILL_STATE_IDLE:
        if (ultrafill_current_fault == ULTRAFILL_FAULT_NONE)
        {
            if (ultrafill_read_hp_pressure() >= ULTRAFILL_HP_FULL_ADC_COUNTS)
            {
                // Already full
                ultrafill_state = ULTRAFILL_STATE_FULL;
                break;
            }
            // Start filling
            ultrafill_start_filling();
            ultrafill_state = ULTRAFILL_STATE_FILLING;
        }
        break;
    case ULTRAFILL_STATE_FILLING:
        if (ultrafill_read_hp_pressure() >= ULTRAFILL_HP_FULL_ADC_COUNTS)
        {
            // Tank is fill stop filling
            ultrafill_stop_filling();
            ultrafill_state = ULTRAFILL_STATE_FULL;
        }
        break;
    case ULTRAFILL_STATE_FULL:
        if (ultrafill_read_hp_pressure() < (ULTRAFILL_HP_FULL_ADC_COUNTS - 200))
        {
            // Pressure has dropped try to start filling again
            ultrafill_state = ULTRAFILL_STATE_IDLE;
        }
        break;
    case ULTRAFILL_STATE_FAULT:
        if (ultrafill_current_fault == ULTRAFILL_FAULT_NONE && ++ultrafill_fault_count >= ULTRAFILL_FAULT_RETRY_COUNTS)
        {
            // Try filling again
            ultrafill_state = ULTRAFILL_STATE_IDLE;
        }
        break;
    default:
        // Unknown state, reset to idle
        ultrafill_state = ULTRAFILL_STATE_IDLE;
        break;
    }
    ultrafill_update_leds();
}

void ultrafill_update_leds(void)
{
    switch (ultrafill_state)
    {
    case ULTRAFILL_STATE_IDLE:
        io_set(LED_GREEN, 0);
        io_set(LED_AMBER, 1);
        io_set(LED_RED, 0);
        break;
    case ULTRAFILL_STATE_FILLING:
        io_set(LED_GREEN, 1);
        io_set(LED_AMBER, 1);
        io_set(LED_RED, 0);
        break;
    case ULTRAFILL_STATE_FULL:
        io_set(LED_GREEN, 1);
        io_set(LED_AMBER, 0);
        io_set(LED_RED, 0);
        break;
    case ULTRAFILL_STATE_FAULT:
        io_set(LED_GREEN, 0);
        io_set(LED_AMBER, 0);
        io_set(LED_RED, 1);
        break;
    default:
        // Unknown state, turn off all LEDs
        io_set(LED_GREEN, 0);
        io_set(LED_AMBER, 0);
        io_set(LED_RED, 0);
        break;
    }

    uint16_t hp_count = ultrafill_read_hp_pressure();
    uint8_t level = 0;

    if (hp_count >= ULTRAFILL_HP_FULL_ADC_COUNTS - 200)
    {
        level = 4;
    }
    else if (hp_count >= 2400)
    {
        level = 3;
    }
    else if (hp_count >= 1500)
    {
        level = 2;
    }
    else if (hp_count >= 780)
    {
        level = 1;
    }

    blue_led_set_level(level);
}

uint8_t ultrafill_get_button(void)
{
    return io_read(BUTTON_INPUT);
}