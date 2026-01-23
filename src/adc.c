#include "adc.h"
#include "project_config.h"

void adc_init(void) {
    // Configure ADC12

    ADC12CTL0 |= SHT02 | ADC12ON | MSC | SHT0_8;
    ADC12CTL1 |= CONSEQ_3 | SHP;
    ADC12CTL0 |= REF2_5V | REFON;


}

void adc_setup_channel(uint8_t port_num, uint8_t pin_num, uint8_t chan_num, uint8_t is_last) {

    if (port_num != 6) {
        return; // Invalid port for ADC input
    }
    // Configure ADC12MCTL0 for the specified channel
    if (chan_num >= 16) 
    {
        return; // Invalid channel number
    }
    volatile uint8_t *adc_mctl_reg = (volatile uint8_t *)&ADC12MCTL0 + chan_num; // Get the address of the appropriate ADC12MCTLx register

    *adc_mctl_reg = (pin_num & 0x0F) | (is_last ? EOS : 0x00); // Set the input channel and EOS bit if it's the last channel
}

void adc_start(void) {
    ADC12CTL0 |= ENC;
    ADC12CTL0 |= ADC12SC; // Start conversion
}

uint16_t adc_read(uint8_t channel) {
    return ADC12MEM[channel];
}