/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "include/USB_uart_printf.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_packet.h"
#include "include/USB_descriptor_device.h"
#include "include/USB_descriptor_config.h"
#include "include/USB_setup_strings.h"
#include "include/USB_setup_descriptors.h"

void send_descriptor_to_host() {

  switch (setup->descriptor_type) {

    case USB_DT_DEVICE:     send_device_descriptor_to_host(setup->length);          break;  
    case USB_DT_CONFIG:     send_configuration_descriptor_to_host(setup->length);   break;
    case USB_DT_STRING:     send_device_string_to_host(setup->descriptor_index);    break;
    default:                error_unknown_descriptor_type(setup->descriptor_type);  break;
           
  }
  
}

static inline void send_device_descriptor_to_host(uint16_t setup_length) { 
  
  uint16_t descriptor_bytes = pico_device_descriptor[0];

  if (setup_length != descriptor_bytes) descriptor_bytes = DEVICE_DESCRIPTOR_DEFAULT_SIZE;
 
  start_control_transfer_to_host(pico_device_descriptor, descriptor_bytes);

}

static inline void send_configuration_descriptor_to_host(uint16_t setup_length) { 
   
  uint16_t descriptor_bytes = pico_config_descriptor[0];
 
  if (setup_length == config_total_length()) descriptor_bytes = config_total_length();

  start_control_transfer_to_host(pico_config_descriptor, descriptor_bytes);

}

static inline void error_unknown_descriptor_type(uint8_t descriptor_type) {

  uart_printf("Setup error, unknown descriptor type=%d\n\r", descriptor_type);

  send_zlp_to_host(0);

}