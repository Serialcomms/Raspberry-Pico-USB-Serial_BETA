/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_error.h"
#include "include/USB_cdc_line_control.h"
#include "include/USB_cdc_line_coding.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_packet.h"
#include "include/USB_data_packet.h"
#include "include/USB_build_endpoints.h"
#include "include/USB_buffer_control.h"

bool CDC_CONFIGURATION_SET = false;

void usb_set_configuration(uint8_t configuration_number) {

  if (configuration_number == 1) {

    usb_build_function_endpoints();

    cdc_class_set_default_line_coding();
    cdc_class_set_default_line_state();
    cdc_class_set_notify_line_state(true);
   
    start_async_receive_data_packet(2, 64);

    CDC_CONFIGURATION_SET = true;

  } else {

    CDC_CONFIGURATION_SET = false;

    usb_error(USB_ERROR_LEVEL_ERROR);

  }

  send_zlp_to_host(0);
  
}