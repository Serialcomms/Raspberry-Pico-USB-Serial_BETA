/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#include "hardware/irq.h"

irq_handler_t __time_critical_func (core1_printf)();

void __time_critical_func (uart_printf)(uint8_t *printf_text, ...);

void initialise_uart_0();

void initialise_uart_1();

void initialise_uart_printf();

void __time_critical_func (core1_entry)();