/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define DEVICE_ADDRESS_MASK 0x7F

#define usb_hardware_set   ((usb_hw_t *)hw_set_alias_untyped(usb_hw))
#define usb_hardware_clear ((usb_hw_t *)hw_clear_alias_untyped(usb_hw))

uint8_t get_pico_device_address();

void set_pico_device_address(uint16_t DEVICE_ADDRESS);