#ifndef RGB_LED_H
#define RGB_LED_H

#include "pico/stdlib.h"

// Initialize RGB LED pins
void rgb_led_init(uint r_pin, uint g_pin, uint b_pin);

// Set RGB LED color
void rgb_led_set(int r, int g, int b);

#endif
