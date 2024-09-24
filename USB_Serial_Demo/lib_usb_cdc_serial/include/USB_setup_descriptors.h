/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Descriptor types
#define USB_DT_DEVICE                   0x01
#define USB_DT_CONFIG                   0x02
#define USB_DT_STRING                   0x03
#define USB_DT_INTERFACE                0x04
#define USB_DT_ENDPOINT                 0x05

void send_descriptor_to_host();

static inline void send_device_descriptor_to_host(uint16_t request_size);
static inline void send_configuration_descriptor_to_host(uint16_t command_length);
static inline void error_unknown_descriptor_type(uint8_t descriptor_type);