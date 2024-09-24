
/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define usb_hardware_set   ((usb_hw_t *)hw_set_alias_untyped(usb_hw))
#define usb_hardware_clear ((usb_hw_t *)hw_clear_alias_untyped(usb_hw))

#define buffer_status_bit_host 0x1
#define buffer_status_bit_pico 0x2
#define buffer_direction_to_host 0
#define buffer_direction_to_pico 1

void usb_handle_buffer_status();

uint32_t get_buffer_mask_to_host(uint8_t EP_NUMBER);
uint32_t get_buffer_mask_to_pico(uint8_t EP_NUMBER);

void clear_buffer_status_to_host(uint8_t EP_NUMBER);
void clear_buffer_status_to_pico(uint8_t EP_NUMBER);

bool get_buffer_status_complete_to_host(uint8_t EP_NUMBER);
bool get_buffer_status_complete_to_pico(uint8_t EP_NUMBER);

static inline void usb_handle_buffer_status_host(uint8_t EP_NUMBER);
static inline void usb_handle_buffer_status_pico(uint8_t EP_NUMBER);

static inline void buffer_completion_default_host(uint8_t EP_NUMBER);
static inline void buffer_completion_default_pico(uint8_t EP_NUMBER);