/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h" 

#include "include/USB_buffer_control.h"
#include "include/USB_build_endpoints.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoints_host.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_EP0_handlers.h"
#include "include/USB_EP1_handlers.h"
#include "include/USB_EP3_handlers.h"
#include "include/USB_uart_printf.h"

void usb_build_default_endpoints() {

  usb_build_host_endpoint(0, USB_TRANSFER_TYPE_CONTROL, 128, &ep0_handler_to_host);
  usb_build_pico_endpoint(0, USB_TRANSFER_TYPE_CONTROL, 128, &ep0_handler_to_pico);

}

void usb_build_function_endpoints() {

  uart_printf("USB Build CDC Function Endpoints\n\r");

  usb_build_host_endpoint(1, USB_TRANSFER_TYPE_BULK, 1024, &ep1_handler_to_host);
  usb_build_pico_endpoint(1, USB_TRANSFER_TYPE_BULK, 1024, &ep1_handler_to_pico);

  usb_build_host_endpoint(3, USB_TRANSFER_TYPE_INTERRUPT, 0, &ep3_handler_to_host);
 
}
