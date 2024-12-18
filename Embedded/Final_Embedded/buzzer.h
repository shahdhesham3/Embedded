#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

// Initialize buzzer on given GPIO pin
void buzzer_init(uint gpio_pin);

// Turn on the buzzer
void buzzer_on(void);

// Turn off the buzzer
void buzzer_off(void);

#endif
