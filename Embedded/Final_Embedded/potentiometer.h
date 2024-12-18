#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "pico/stdlib.h"

// Initialize the potentiometer ADC
void potentiometer_init(void);

// Read voltage from the potentiometer pin
float potentiometer_read_voltage(uint pin);

#endif
