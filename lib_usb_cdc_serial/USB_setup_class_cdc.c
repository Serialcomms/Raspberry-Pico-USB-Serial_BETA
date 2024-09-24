/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_error.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_packet.h"
#include "include/USB_setup_device.h"
#include "include/USB_setup_interface.h"
#include "include/USB_setup_type_class.h"
#include "include/USB_com_port_signalling.h"
#include "include/USB_cdc_line_coding.h"
#include "include/USB_cdc_line_control.h"
#include "include/USB_setup_class_cdc.h"

void usb_setup_class_cdc() {

  switch (setup->request) {

   case CDC_CLASS_GET_LINE_CODING:  cdc_class_get_line_coding();    break;
   case CDC_CLASS_SET_LINE_CODING:  cdc_class_set_line_coding();    break;
   case CDC_CLASS_SET_LINE_CONTROL: cdc_class_set_line_control();   break;
   case CDC_CLASS_SET_LINE_BREAK:   cdc_class_set_line_break();     break;

   default: usb_setup_class_cdc_unknown();  break;

  }

}

static inline void usb_setup_class_cdc_unknown() {

  usb_error(USB_ERROR_LEVEL_ERROR);

  send_zlp_to_host(0);

}