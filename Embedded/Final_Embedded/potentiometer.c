#include "potentiometer.h"
#include "hardware/adc.h"

// Initialize ADC for the potentiometer
void potentiometer_init(void) {
    adc_init(); // Initialize ADC hardware
}

// Read voltage from the potentiometer pin
float potentiometer_read_voltage(uint pin) {
    adc_select_input(pin - 26); // Convert GPIO pin to ADC input channel (pin 26 is ADC0)
    uint16_t raw = adc_read();
    return raw * (3.3f / 4095.0f); // Scale to 3.3V
}
