#include "pico/stdlib.h"
#include "potentiometer.h"
#include "dht_driver.h"
#include "lcd_driver.h"
#include "rgb_led.h"
#include "light_sensor.h"
#include "buzzer.h"
#include <stdio.h>  

// Pin Definitions for Raspberry Pi Pico
#define POT_PIN 28        // Potentiometer pin to simulate battery voltage
#define LDR_PIN 26        // Light sensor pin (LDR)
#define DHT_PIN 19        // DHT11 Temperature and Humidity Sensor Pin
#define RED_PIN 2         // RGB LED Red Pin
#define GREEN_PIN 3       // RGB LED Green Pin
#define BLUE_PIN 4        // RGB LED Blue Pin
#define BUZZER_PIN 10     // Buzzer Pin

void setRGB(int r, int g, int b) {
    rgb_led_set(r, g, b);
}

void setup() {
    // Initialize components
    potentiometer_init();
    dht_init(DHT_PIN);
    lcd_init();
    rgb_led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    light_sensor_init(LDR_PIN);
    buzzer_init(BUZZER_PIN);

    // Display initial message
    lcd_display("Car Battery Monitor");
}

void loop() {
    // === Potentiometer for Battery Voltage ===
    float batteryVoltage = potentiometer_read_voltage(POT_PIN);
    int batteryPercent = (int)(batteryVoltage / 7.4 * 100);  // Example scaling to 0-100%

    // === Read DHT11 Sensor ===
    float dhtTemperature = dht_read_temperature(); // Temperature in °C
    float humidity = dht_read_humidity();          // Humidity in %

    // === Light Sensor (LDR) ===
    bool isDark = light_sensor_is_dark();

    // === Display Data on LCD ===
    char message[50];
    snprintf(message, sizeof(message), "Battery: %d%% Voltage: %.2fV", batteryPercent, batteryVoltage);
    lcd_display(message);

    snprintf(message, sizeof(message), "Temp: %.1fC Humidity: %.1f%%", dhtTemperature, humidity);
    lcd_display(message);

    snprintf(message, sizeof(message), "Light: %s", isDark ? "Dark" : "Bright");
    lcd_display(message);

    // === Control RGB LED Based on Temperature ===
    if (dhtTemperature < 20) {
        setRGB(0, 0, 255); // Blue for low temperature
    } else if (dhtTemperature >= 20 && dhtTemperature < 30) {
        setRGB(0, 255, 0); // Green for normal temperature
    } else {
        setRGB(255, 0, 0); // Red for high temperature
    }

    // === Activate Buzzer if Light Intensity is Low ===
    if (isDark) {
        buzzer_on();  // Turn on buzzer
    } else {
        buzzer_off();   // Turn off buzzer
    }

    // Wait 1 second before repeating
    sleep_ms(1000);
}

int main() {
    stdio_init_all();

    // Initialize all components
    setup();

    // Main loop
    while (true) {
        loop();
    }

    return 0;
}
