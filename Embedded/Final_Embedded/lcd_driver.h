#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "pico/stdlib.h"

// Function declarations
void lcd_init(void);         // Initialize the LCD
void lcd_clear(void);        // Clear the LCD display
void lcd_print(const char *message);  // Print a string on the LCD
void lcd_display(const char *message); // Display a string, clearing first

#endif
