/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_error.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_packet.h"
#include "include/USB_setup_interface.h"

void usb_setup_interface() {

  setup->direction ? setup_interface_respond_to_host() : setup_interface_request_to_pico();

}

static inline void setup_interface_respond_to_host() {

    setup_interface_unknown();

}

static inline void setup_interface_request_to_pico() {

    setup_interface_unknown();
}

static inline void setup_interface_unknown() {

    usb_error(USB_ERROR_LEVEL_ERROR);

    send_zlp_to_host(0);

}