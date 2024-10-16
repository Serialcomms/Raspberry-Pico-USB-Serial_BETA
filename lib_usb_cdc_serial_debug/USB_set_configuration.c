/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "include/USB_cdc_line_control.h"
#include "include/USB_cdc_line_coding.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_packet.h"
#include "include/USB_data_packet.h"
#include "include/USB_build_endpoints.h"
#include "include/USB_uart_printf.h"
#include "include/USB_buffer_control.h"

bool CDC_CONFIGURATION_SET = false;

void usb_set_configuration(uint8_t configuration_number) {

  uart_printf("USB Set CDC Configuration, Number=%d\n\r", configuration_number);

  if (configuration_number == 1) {

    usb_build_function_endpoints();

    cdc_class_set_default_line_coding();
    cdc_class_set_default_line_state();
    cdc_class_set_notify_line_state(true);

    set_next_data_pid_to_host(3, 0);

    set_next_data_pid_to_host(1, 0);
    set_next_data_pid_to_pico(1, 0);
    
    start_async_receive_data_packet(1, 64);

    CDC_CONFIGURATION_SET = true;

    uart_printf("USB Set CDC Configuration ++++++++++++++++++++++++++++++++++++\n\r");


  } else {

    CDC_CONFIGURATION_SET = false;

    uart_printf("USB Set CDC Configuration, Number Requested is Zero or Invalid\n\r");

  }

  send_zlp_to_host(0);
  
}