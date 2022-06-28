cmake_minimum_required(VERSION 3.13)
option(TESTING_ENVIRONMENT "Download compile and provide gtest/gmock" OFF)

if(NOT TESTING_ENVIRONMENT)
include(pico_sdk_import.cmake)
endif()
project(sprinkler_control C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


if(NOT TESTING_ENVIRONMENT)
pico_sdk_init()
endif()

if(TESTING_ENVIRONMENT)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(utils)

if(NOT TESTING_ENVIRONMENT)
add_subdirectory(hw)

add_executable(control
        control.cpp
        )

pico_generate_pio_header(control ${CMAKE_CURRENT_LIST_DIR}/uart_rx.pio)


# pull in common dependencies
target_link_libraries(control
        pico_stdlib
        pico_multicore
        hardware_pio
        hw
        utils
)

# create map/bin/hex file etc.
pico_add_extra_outputs(control)

pico_enable_stdio_usb(control 1)
pico_enable_stdio_uart(control 1)

endif()