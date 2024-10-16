/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdarg.h>
#include "pico/sync.h" 
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/uart.h"
#include "pico/util/queue.h"
#include "include/USB_uart_printf.h"

#include "pico/multicore.h"

queue_t uart_fifo_queue;

uint8_t UART_line_buffer[128];

va_list core1_args;

uint8_t *core1_printf_text;

semaphore_t core_1_sem;

void initialise_uart_printf() {

    multicore_launch_core1(core1_entry);

    multicore_fifo_clear_irq();

    sem_init(&core_1_sem, 1, 1);
 
    queue_init(&uart_fifo_queue, sizeof(uint8_t), 0x4000);
}   

void initialise_uart_0() {

    uart_init(uart0, 115200);

    uart_set_fifo_enabled(uart0, true);

    uart_set_irq_enables(uart0, false, false);

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

}

void initialise_uart_1() {

    uart_init(uart1, 115200);

    uart_set_fifo_enabled(uart1, true);

    uart_set_irq_enables(uart1, false, false);

    gpio_set_function(4, GPIO_FUNC_UART);
    gpio_set_function(5, GPIO_FUNC_UART);

}

void __time_critical_func (core1_entry)() {

    bool uart_writable;
    
    uint16_t queue_length;
    
    static uint8_t printf_char;

    //initialise_uart_0();

    initialise_uart_1();

    multicore_fifo_clear_irq();

    irq_set_exclusive_handler(SIO_FIFO_IRQ_NUM(1), (irq_handler_t) core1_printf);
    
    irq_set_enabled(SIO_FIFO_IRQ_NUM(1), true);

    while (true) {

        uart_writable = uart_is_writable(uart1);

        queue_length = queue_get_level(&uart_fifo_queue);
     
        if (uart_writable && queue_length > 0) {

            if (queue_try_remove(&uart_fifo_queue, &printf_char)) {

                uart_putc_raw(uart1, printf_char);
            }

        } 
       
    }

}

void __time_critical_func (uart_printf)(uint8_t *printf_text, ...) {

    core1_printf_text = printf_text;
    
    va_start(core1_args, printf_text);

    va_end(core1_args);

    bool core_1_busy;

    sem_acquire_blocking(&core_1_sem);

    multicore_fifo_push_blocking(1);

    do {

        core_1_busy = (sem_available(&core_1_sem) == 0);

    } while (core_1_busy);

}

irq_handler_t __time_critical_func (core1_printf)() {

    multicore_fifo_pop_blocking();
    
    multicore_fifo_clear_irq();

    uint16_t printf_offset = 0;

    uint16_t printf_length = vsnprintf(UART_line_buffer, sizeof(UART_line_buffer), core1_printf_text, core1_args);
   
    do {

        if (queue_try_add(&uart_fifo_queue, &UART_line_buffer[printf_offset])) {

            ++printf_offset;
        }
        
    } while (--printf_length);

    sem_release(&core_1_sem);

}