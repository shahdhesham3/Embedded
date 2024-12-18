#include "lcd_driver.h"
#include "hardware/spi.h"
#include <string.h>

#define SPI_PORT spi1       // Use SPI1 for communication
#define PIN_RST 12          // Reset pin for the LCD
#define PIN_CE  13          // Chip enable (CS) pin for the LCD
#define PIN_DC  11          // Data/Command pin for the LCD
#define PIN_DIN 15          // Data input (MOSI) pin for the LCD
#define PIN_CLK 14          // Clock pin (SCK) for the LCD

// Basic font - 5x7 pixel font for ASCII characters
static const uint8_t font[96][5] = {
    // Character data for ASCII characters 32-127, stored as 5 bytes for each character
    // This is just an example, you can use a more complete font table
    // A simple placeholder for illustration purposes
    {0x00, 0x00, 0x00, 0x00, 0x00}, // Space (32)
    {0x00, 0x00, 0x5f, 0x00, 0x00}, // '!'
    {0x00, 0x07, 0x00, 0x07, 0x00}, // '"'
    // ... Add more characters as needed
};

// Function to send a command to the LCD
static void lcd_send_command(uint8_t command) {
    gpio_put(PIN_DC, 0); // Set DC pin to LOW for command
    gpio_put(PIN_CE, 0);  // Set CE pin to LOW (select the LCD)
    spi_write_blocking(SPI_PORT, &command, 1); // Send the command
    gpio_put(PIN_CE, 1);  // Deselect the LCD (CE HIGH)
}

// Function to send data to the LCD
static void lcd_send_data(uint8_t data) {
    gpio_put(PIN_DC, 1); // Set DC pin to HIGH for data
    gpio_put(PIN_CE, 0);  // Set CE pin to LOW (select the LCD)
    spi_write_blocking(SPI_PORT, &data, 1); // Send the data
    gpio_put(PIN_CE, 1);  // Deselect the LCD (CE HIGH)
}

// Function to initialize the LCD
void lcd_init(void) {
    spi_init(SPI_PORT, 4000000); // Initialize SPI at 4MHz
    gpio_set_function(PIN_CLK, GPIO_FUNC_SPI);  // Set the clock pin for SPI
    gpio_set_function(PIN_DIN, GPIO_FUNC_SPI);  // Set the data pin for SPI

    // Initialize control pins
    gpio_init(PIN_RST);
    gpio_init(PIN_CE);
    gpio_init(PIN_DC);
    gpio_set_dir(PIN_RST, GPIO_OUT);  // Set as output
    gpio_set_dir(PIN_CE, GPIO_OUT);  // Set as output
    gpio_set_dir(PIN_DC, GPIO_OUT);  // Set as output

    gpio_put(PIN_RST, 0);  // Reset the LCD
    sleep_ms(100);         // Wait for a while
    gpio_put(PIN_RST, 1);  // Release the reset

    // Send initialization commands to the LCD
    lcd_send_command(0x21);  // Extended command mode
    lcd_send_command(0xB1);  // Set contrast (0x80 - 0xBF)
    lcd_send_command(0x04);  // Set temperature coefficient
    lcd_send_command(0x14);  // Set bias mode (1:48)
    lcd_send_command(0x20);  // Basic command mode
    lcd_send_command(0x0C);  // Normal display mode

    lcd_clear();  // Clear the screen after initialization
}

// Function to clear the LCD screen
void lcd_clear(void) {
    for (int i = 0; i < 504; i++) {
        lcd_send_data(0x00);  // Send 0 to clear the screen
    }
}

// Function to print a message on the LCD
void lcd_print(const char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        uint8_t c = message[i] - 32;  // Convert to font index (ASCII 32 = space)
        if (c < 96) {
            for (int j = 0; j < 5; j++) {
                lcd_send_data(font[c][j]);  // Send each byte for the character
            }
            lcd_send_data(0x00);  // 1 byte space between characters
        }
    }
}

// Function to display a message, clearing the screen first
void lcd_display(const char *message) {
    lcd_clear();  // Clear the display first
    lcd_print(message);  // Print the message
}
