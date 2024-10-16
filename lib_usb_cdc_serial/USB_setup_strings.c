/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "include/USB_error.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_strings.h"

uint8_t string_buffer[128];

const uint8_t *pico_string_descriptors[] = {
  
    [0] = LANGUAGE_ENGLISH_US,          // Language ID US English
    [1] = "Raspberry Pi",               // Vendor
    [2] = "Pico CDC Serial",            // Product
    [3] = "Pico CDC Interface",         // Interface
    [4] = "Pico Spare String"           // spare string

};

void send_device_string_to_host(uint8_t string_index) { 

    string_index ? send_text_string(string_index) : send_language_string();

}

static inline void send_text_string(uint8_t string_index) {

    if (string_index < count_of(pico_string_descriptors)) {

        uint8_t string_length = usb_convert_string_descriptor(string_index);

        start_control_transfer_to_host(string_buffer, string_length);  
      
    } else {

        usb_error(USB_ERROR_LEVEL_ERROR);

        send_zlp_to_host(0);

    }

}

static inline void send_language_string() {

    const uint8_t *language = pico_string_descriptors[0];

    string_buffer[0] = USB_DESCRIPTOR_LANGID_SIZE;
    string_buffer[1] = USB_DESCRIPTOR_TYPE_STRING;
    string_buffer[2] = language[0];
    string_buffer[3] = language[1];

    start_control_transfer_to_host(string_buffer, USB_DESCRIPTOR_LANGID_SIZE);  

}

static inline uint8_t usb_convert_string_descriptor(uint8_t string_index) {

    const uint8_t *ascii_string = pico_string_descriptors[string_index];

    uint8_t string_length = MIN(strlen(ascii_string), 62);

    uint8_t buffer_length = 2 + (2 * string_length);
    uint8_t i = 1; 
    uint8_t j = 0;

    string_buffer[0] = buffer_length;
    string_buffer[1] = USB_DESCRIPTOR_TYPE_STRING;

    do {

        string_buffer[++i] = *ascii_string++ & 0x7f;
        string_buffer[++i] = 0;

    } while (++j < string_length);   
  
    return buffer_length;
}