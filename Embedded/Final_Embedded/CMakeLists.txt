cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Final_Embedded C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(Final_Embedded 
    main.c 
    dht_driver.c
    buzzer.c
    lcd_driver.c
    rgb_led.c
    light_sensor.c
    potentiometer.c
    dwm_pico_5110_LCD.c  # Ensure the file extension is correct
)


# Set program name and version
pico_set_program_name(Final_Embedded "Final_Embedded")
pico_set_program_version(Final_Embedded "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Final_Embedded 0)
pico_enable_stdio_usb(Final_Embedded 1)

# Add the standard library to the build
target_link_libraries(Final_Embedded
    pico_stdlib
    hardware_spi
    hardware_adc
    hardware_gpio
)

# Add the standard include files to the build
target_include_directories(Final_Embedded PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/dwm_pico_5110_LCD  # Include path for dwm_pico_5110_LCD header
)

# Generate extra outputs (like UF2 file)
pico_add_extra_outputs(Final_Embedded)
