/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stdbool.h"
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "include/USB_error.h"
#include "include/USB_setup_control.h"
#include "include/USB_buffer_control.h"
#include "include/USB_data_packet.h"
#include "include/USB_setup_packet.h"
#include "include/USB_cdc_line_control.h"
#include "include/USB_com_port_signalling.h"

com_port_t pico_com_port;

const bool REBOOT_PICO_TO_BOOTSEL_ON_BREAK = true; 
// From PuTTY > Special Command > Break

void cdc_class_set_line_break() {

  int16_t break_duration = setup->value;

  busy_wait_ms(1000);

  send_zlp_to_host(0);

  if (REBOOT_PICO_TO_BOOTSEL_ON_BREAK) {

    usb_error(USB_ERROR_LEVEL_BOOT);

    busy_wait_ms(3000);

    reset_usb_boot(PICO_DEFAULT_LED_PIN, 0);

  }

}

void com_port_set_dsr(bool new_state) {

  if (new_state ^ pico_com_port.signalling.DCE.DSR) {

    pico_com_port.signalling.DCE.DSR = new_state;

    cdc_class_set_notify_line_state(true);

  }

}

void com_port_set_dcd(bool new_state) {

  if (new_state ^ pico_com_port.signalling.DCE.DCD) {

    pico_com_port.signalling.DCE.DCD = new_state;

    cdc_class_set_notify_line_state(true);

  }

}

void com_port_set_ring(bool new_state) {

  if (new_state ^ pico_com_port.signalling.DCE.RING) {

    pico_com_port.signalling.DCE.RING = new_state;

    cdc_class_set_notify_line_state(true);
    
  }

}

bool com_port_get_dtr() {

  return pico_com_port.signalling.DTE.DTR;

}

bool com_port_get_rts() {

  return pico_com_port.signalling.DTE.RTS;
  
}

bool com_port_get_dsr() {

  return pico_com_port.signalling.DCE.DSR;

}

bool com_port_get_dcd() {

  return pico_com_port.signalling.DCE.DCD;

}