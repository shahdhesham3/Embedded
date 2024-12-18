#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "pico/stdlib.h"

// Initialize light sensor pin
void light_sensor_init(uint pin);

// Read light sensor status
bool light_sensor_is_dark(void);

#endif
