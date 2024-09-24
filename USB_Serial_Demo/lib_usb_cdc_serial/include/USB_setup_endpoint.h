/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define buffer_direction_to_host 0
#define buffer_direction_to_pico 1

#define USB_REQUEST_SET_FEATURE     0x03
#define USB_REQUEST_CLEAR_FEATURE   0x01

void usb_setup_endpoint();

static inline void setup_endpoint_respond_to_host();
static inline void setup_endpoint_request_to_pico();
static inline void setup_endpoint_request_unknown();
static inline void setup_endpoint_clear_feature(uint8_t EP_NUMBER);