/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "include/USB_uart_printf.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_packet.h"
#include "include/USB_setup_device.h"
#include "include/USB_setup_interface.h"
#include "include/USB_setup_type_standard.h"

void usb_setup_type_standard() {

    switch (setup->recipient) {

        case USB_REQ_TYPE_RECIPIENT_DEVICE:         usb_setup_device();     break;
        case USB_REQ_TYPE_RECIPIENT_INTERFACE:      usb_setup_interface();  break;
        case USB_REQ_TYPE_RECIPIENT_ENDPOINT:       usb_setup_unknown();    break;

        default:                                    usb_setup_unknown();    break;
        
    } 

}

static inline void usb_setup_unknown() {

    uart_printf("Setup Standard Request, unknown recipient=%d, type=%d, direction=%d, request=%d, value=%d, index=%d, length=%d \n\r", 
    setup->recipient, setup->request_type, setup->direction, 
    setup->request, setup->value, setup->index, setup->length);

    send_zlp_to_host(0);

}