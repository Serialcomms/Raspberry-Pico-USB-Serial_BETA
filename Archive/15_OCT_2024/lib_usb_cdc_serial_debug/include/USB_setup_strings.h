/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define LANGUAGE_GERMAN     "\x04\x07"
#define LANGUAGE_ENGLISH_US "\x09\x04"
#define LANGUAGE_AUSTRALIAN "\x0C\x04"

#define USB_DESCRIPTOR_LANGID_SIZE 0x04
#define USB_DESCRIPTOR_TYPE_STRING 0x03

static inline void send_language_string();
static inline void send_text_string(uint8_t string_index);
static inline uint8_t usb_convert_string_descriptor(uint8_t string_index);

void send_device_string_to_host(uint8_t STRING_INDEX);