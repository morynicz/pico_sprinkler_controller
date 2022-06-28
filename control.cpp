/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include <vector>
#include "pico/multicore.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "uart_rx.pio.h"
// #include "utils/io_testing.hpp"

#include <iostream>

#define SERIAL_BAUD PICO_DEFAULT_UART_BAUD_RATE
#define HARD_UART_INST uart1

// You'll need a wire from GPIO4 -> GPIO3
#define HARD_UART_TX_PIN 4
#define PIO_RX_PIN 2
#define PIO_TX_PIN 3

// Ask core 1 to print a string, to make things easier on core 0
void core1_main() {
    const char *s = (const char *) multicore_fifo_pop_blocking();
    uart_puts(HARD_UART_INST, s);
}

void setOuts(const std::vector<uint>& outs)
{
    for(auto out : outs)
    {
        gpio_init(out);
        gpio_set_dir(out, GPIO_OUT);
    }
}

void blinkLed(uint out)
{
    gpio_put(out, 1);
    sleep_ms(250);
    gpio_put(out, 0);
}

void blinkMany(std::vector<uint>& outs)
{
    for(auto out: outs)
        gpio_put(out, 1);
    sleep_ms(250);
    for(auto out: outs)
        gpio_put(out, 0);
}

std::vector<uint> numToDisp(const std::vector<uint>& outs, char in)
{
    std::vector<uint> result;
    for(int i =0; i < 1<<outs.size(); i = i <<1)
    {
        if(in & i)
        {
            result.push_back(outs.at(i));
        }
    }
    return result;
}

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;

    std::vector<uint> outs{10,11,12,13};
    std::vector<uint> disp{16,17,18,19,20,21};

    setOuts(outs);
    setOuts(disp);
    setOuts({25});

    // Set up the state machine we're going to use to receive them.
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &uart_rx_program);
    uart_rx_program_init(pio, sm, offset, PIO_RX_PIN, SERIAL_BAUD);



    for(auto out : outs)
    {
        blinkLed(out);
    }

    blinkMany(outs);
    blinkMany(disp);

    blinkLed(25);

    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    char i = 0;
    while (true) {
        std::cout << "test" <<std::endl;
        // gpio_put(LED_PIN, 1);
        // sleep_ms(250);
        // gpio_put(LED_PIN, 0);
        // sleep_ms(250);
    auto dis = numToDisp(disp, i);
    i++;
    i = i % 64;


            // Echo characters received from PIO to the console
    // while (true) {
        // char id = uart_rx_program_getc(pio, sm);
        // char time = uart_rx_program_getc(pio, sm);
        // putchar(c);
        // std::cout << c;
        // if(c != 0)
        // {
        //     blinkLed(outs.at(c%4));
        // }
    }
#endif
}







/*
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "uart_rx.pio.h"

// This program
// - Uses UART1 (the spare UART, by default) to transmit some text
// - Uses a PIO state machine to receive that text
// - Prints out the received text to the default console (UART0)
// This might require some reconfiguration on boards where UART1 is the
// default UART.

#define SERIAL_BAUD PICO_DEFAULT_UART_BAUD_RATE
#define HARD_UART_INST uart1

// You'll need a wire from GPIO4 -> GPIO3
#define HARD_UART_TX_PIN 4
#define PIO_RX_PIN 3

// Ask core 1 to print a string, to make things easier on core 0
void core1_main() {
    const char *s = (const char *) multicore_fifo_pop_blocking();
    uart_puts(HARD_UART_INST, s);
}

int main() {
    // Console output (also a UART, yes it's confusing)
    setup_default_uart();
    printf("Starting PIO UART RX example\n");

    // Set up the hard UART we're going to use to print characters
    uart_init(HARD_UART_INST, SERIAL_BAUD);
    gpio_set_function(HARD_UART_TX_PIN, GPIO_FUNC_UART);

    // Set up the state machine we're going to use to receive them.
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &uart_rx_program);
    uart_rx_program_init(pio, sm, offset, PIO_RX_PIN, SERIAL_BAUD);

    // Tell core 1 to print some text to uart1 as fast as it can
    multicore_launch_core1(core1_main);
    const char *text = "Hello, world from PIO! (Plus 2 UARTs and 2 cores, for complex reasons)\n";
    multicore_fifo_push_blocking((uint32_t) text);

    // Echo characters received from PIO to the console
    while (true) {
        char c = uart_rx_program_getc(pio, sm);
        putchar(c);
    }
}
*/