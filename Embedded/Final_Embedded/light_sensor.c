#include "light_sensor.h"

static uint sensor_pin;

void light_sensor_init(uint pin) {
    sensor_pin = pin;
    gpio_init(sensor_pin);
    gpio_set_dir(sensor_pin, GPIO_IN);
}

bool light_sensor_is_dark(void) {
    return gpio_get(sensor_pin) == 0; // Assume LOW = dark
}
