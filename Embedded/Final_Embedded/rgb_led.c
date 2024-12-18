#include "rgb_led.h"

static uint red_pin, green_pin, blue_pin;

void rgb_led_init(uint r_pin, uint g_pin, uint b_pin) {
    red_pin = r_pin;
    green_pin = g_pin;
    blue_pin = b_pin;

    gpio_init(red_pin);
    gpio_init(green_pin);
    gpio_init(blue_pin);

    gpio_set_dir(red_pin, GPIO_OUT);
    gpio_set_dir(green_pin, GPIO_OUT);
    gpio_set_dir(blue_pin, GPIO_OUT);
}

void rgb_led_set(int r, int g, int b) {
    gpio_put(red_pin, r);
    gpio_put(green_pin, g);
    gpio_put(blue_pin, b);
}
