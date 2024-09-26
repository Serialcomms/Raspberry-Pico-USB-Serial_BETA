/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "pico/stdlib.h" 

#include "include/USB_buffer_control.h"
#include "include/USB_build_endpoints.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoints_host.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_EP0_handlers.h"
#include "include/USB_EP1_handlers.h"
#include "include/USB_EP2_handlers.h"

void usb_build_default_endpoints() {

  usb_build_host_endpoint(0, USB_TRANSFER_TYPE_CONTROL, 128, &ep0_handler_to_host);
  usb_build_pico_endpoint(0, USB_TRANSFER_TYPE_CONTROL, 128, &ep0_handler_to_pico);

}

void usb_build_function_endpoints() {

  usb_build_host_endpoint(1, USB_TRANSFER_TYPE_INTERRUPT, 64, &ep1_handler_to_host);
  
  usb_build_host_endpoint(2, USB_TRANSFER_TYPE_BULK, 1024, &ep2_handler_to_host);
  usb_build_pico_endpoint(2, USB_TRANSFER_TYPE_BULK, 1024, &ep2_handler_to_pico);
 
}