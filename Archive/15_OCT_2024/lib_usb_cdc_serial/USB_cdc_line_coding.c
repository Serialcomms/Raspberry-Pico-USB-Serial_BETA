/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_error.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_packet.h"
#include "include/USB_data_packet.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_setup_descriptors.h"
#include "include/USB_com_port_signalling.h"
#include "include/USB_com_port_framing.h"
#include "include/USB_buffer_control.h"
#include "include/USB_cdc_line_coding.h"

void cdc_class_get_line_coding() {

  bool valid_settings = valid_framing(pico_com_port.framing.Baud, pico_com_port.framing.Parity, pico_com_port.framing.Stop);

  if (valid_settings) {

   // usb_error(USB_ERROR_LEVEL_NONE);

  } else {

    cdc_class_set_default_line_coding();

    usb_error(USB_ERROR_LEVEL_WARN);

  }

  cdc_class_send_line_coding_to_host();

}

void cdc_class_set_line_coding() {

  uint8_t cdc_interface = setup->index;
  uint8_t setup_length = setup->length;

  set_next_data_pid_to_pico(0, 1);
  
  start_control_transfer_receive_callback(set_line_coding_receive_callback, setup_length);  // initiate control transfer receive stage here
  
}

static inline void set_line_coding_receive_callback(uint8_t *data, uint8_t transfer_bytes) {

  if (transfer_bytes == sizeof(port_framing_t)) {

    cdc_class_set_new_line_coding(data, transfer_bytes); 

  } else {

    cdc_class_set_default_line_coding();

    usb_error(USB_ERROR_LEVEL_ERROR);

  }

  send_zlp_to_host(0);    // complete control transfer stage here

}

static inline void cdc_class_set_new_line_coding(uint8_t *data, uint8_t transfer_bytes) {

  port_framing_t *new_line_coding = (port_framing_t *)data;

  bool settings_valid = valid_framing(new_line_coding->Baud, new_line_coding->Parity,new_line_coding->Stop);

  if (settings_valid) {
    
    pico_com_port.framing.Baud    = new_line_coding->Baud;
    pico_com_port.framing.Data    = new_line_coding->Data;
    pico_com_port.framing.Parity  = new_line_coding->Parity;
    pico_com_port.framing.Stop    = new_line_coding->Stop;

  } else {

    cdc_class_set_default_line_coding();

    usb_error(USB_ERROR_LEVEL_WARN);

  }

}

static inline void cdc_class_send_line_coding_to_host() {

  void *com_port_framing = &pico_com_port.framing;
  uint8_t com_port_framing_size = sizeof(pico_com_port.framing);

  start_control_transfer_to_host(com_port_framing, com_port_framing_size);

}

void cdc_class_set_default_line_coding() {

  pico_com_port.framing.Baud    = 115200;
  pico_com_port.framing.Data    = 8;        // 8 data bits
  pico_com_port.framing.Parity  = 0;        // no parity
  pico_com_port.framing.Stop    = 0;        // 1 stop bit

}