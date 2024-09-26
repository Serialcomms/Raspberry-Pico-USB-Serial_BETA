/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

irq_handler_t __time_critical_func (core1_printf)();

void initialise_uart_printf();

void __time_critical_func (uart_printf)(uint8_t *printf_text, ...);

static inline void initialise_uart_0();
static inline void __time_critical_func (core1_entry)();