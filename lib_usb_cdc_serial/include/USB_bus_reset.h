/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define usb_hardware_set   ((usb_hw_t *)hw_set_alias_untyped(usb_hw))
#define usb_hardware_clear ((usb_hw_t *)hw_clear_alias_untyped(usb_hw))

#define ZERO_ALL_BITS   0x00000000
#define CLEAR_ALL_BITS  0xFFFFFFFF

void usb_handle_bus_reset();
void clear_sie_status_register();

static inline void clear_usb_interrupts();
static inline void clear_buffer_status_register();
static inline void clear_usb_start_of_frame();
static inline void reset_device_address();
void purge_endpoint_function_queues();