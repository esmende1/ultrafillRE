#include "adc.h"
#include "project_config.h"

void adc_init(void) {
    // Configure ADC12
    ADC12CTL0 = SHT0_11 | MSC | REF2_5V | REFON | ADC12ON | ENC; 
    ADC12CTL1 = CONSEQ_3;

}

void adc_setup_channel(uint8_t port, uint8_t pin_num) {

    if (port != 6) {
        return; // Invalid port for ADC input
    }
    // Configure ADC12MCTL0 for the specified channel
    ADC12MCTL0 = (pinnum & 0x0F);
}

void adc_start(void) {
    ADC12CTL0 |= ENC;
    ADC12CTL0 |= ADC12SC; // Start conversion
}

uint16_t adc_read(uint8_t channel) {
    return ADC12MEM0 + (sizeof(ADC12MEM0) * channel); // Read the conversion result from ADC12MEM0
}