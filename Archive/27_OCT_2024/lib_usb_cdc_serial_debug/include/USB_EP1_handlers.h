/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define usb_hardware_set   ((usb_hw_t *)hw_set_alias_untyped(usb_hw))
#define usb_hardware_clear ((usb_hw_t *)hw_clear_alias_untyped(usb_hw))

irq_handler_t __not_in_flash_func(ep1_handler_to_host)(uint8_t EP_NUMBER);
irq_handler_t __not_in_flash_func(ep1_handler_to_pico)(uint8_t EP_NUMBER);

void __not_in_flash_func(add_ep1_data_to_pico_queue)(uint16_t data_length);

static inline void clear_buffer_status(uint32_t buffer_mask);

static inline void __not_in_flash_func (ep1_queue_runner_to_host());

static inline void show_dpram_to_pico(uint8_t EP_NUMBER);
static inline void show_dpram_to_host(uint8_t EP_NUMBER);

static inline void show_character_to_host(uint8_t EP_NUMBER);
static inline void show_character_to_pico(uint8_t EP_NUMBER);

static inline void run_pico_callback_handler();