#ifndef DHT_DRIVER_H
#define DHT_DRIVER_H

#include "pico/stdlib.h"

// Initialize DHT11 sensor on the given GPIO pin
void dht_init(uint gpio_pin);

// Read temperature in Celsius
float dht_read_temperature(void);

// Read humidity percentage
float dht_read_humidity(void);

#endif
