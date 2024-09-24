/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_error.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_device.h"
#include "include/USB_setup_strings.h"
#include "include/USB_setup_packet.h"
#include "include/USB_setup_address.h"
#include "include/USB_setup_descriptors.h"
#include "include/USB_set_configuration.h"

void usb_setup_device() {

  setup->direction ? setup_device_respond_to_host() : setup_device_request_to_pico();

}

static inline void setup_device_respond_to_host() {

  switch(setup->request) {

    case USB_REQUEST_GET_DESCRIPTOR:      send_descriptor_to_host();                break;
    case USB_REQUEST_GET_CONFIGURATION:   setup_request_unknown(setup->request);    break;
    case USB_REQUEST_GET_STATUS:          setup_request_unknown(setup->request);    break;
    default:                              setup_request_unknown(setup->request);    break;

  }

}

static inline void setup_device_request_to_pico() {

  switch(setup->request) {
  
    case USB_REQUEST_SET_ADDRESS:         set_pico_device_address(setup->value);    break;
    case USB_REQUEST_SET_CONFIGURATION:   usb_set_configuration(setup->value);      break;
    default:                              setup_request_unknown(setup->request);    break;                            

  }

}

static inline void setup_request_unknown(uint8_t request_type) {

  usb_error(USB_ERROR_LEVEL_ERROR);

  send_zlp_to_host(0);

}