cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(sprinkler_control C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()



add_executable(control
        control.cpp
        )

pico_generate_pio_header(control ${CMAKE_CURRENT_LIST_DIR}/uart_rx.pio)


# pull in common dependencies
target_link_libraries(control pico_stdlib pico_multicore hardware_pio)

# create map/bin/hex file etc.
pico_add_extra_outputs(control)

pico_enable_stdio_usb(control 1)
pico_enable_stdio_uart(control 1)

