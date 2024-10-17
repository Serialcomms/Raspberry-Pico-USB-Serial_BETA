/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "include/USB_error.h"
#include "include/USB_setup_packet.h"
#include "include/USB_setup_device.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_interface.h"
#include "include/USB_setup_class_cdc.h"
#include "include/USB_setup_type_class.h"

void usb_setup_type_class() {

    switch (setup->recipient) {

        case USB_REQ_TYPE_RECIPIENT_DEVICE:         usb_setup_class_unknown();      break;
        case USB_REQ_TYPE_RECIPIENT_INTERFACE:      usb_setup_class_cdc();          break;
        case USB_REQ_TYPE_RECIPIENT_ENDPOINT:       usb_setup_class_unknown();      break;

        default:                                    usb_setup_class_unknown();      break;
        
    } 

}

static inline void usb_setup_class_unknown() {

    usb_error(USB_ERROR_LEVEL_ERROR);

    send_zlp_to_host(0);

}