/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/regs/usb.h"
#include "hardware/structs/usb.h"
#include "include/USB_error.h"

#include "include/USB_setup_packet.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_type_class.h"
#include "include/USB_setup_type_standard.h"
#include "include/USB_buffer_control.h"

usb_setup_t setup_command;
usb_setup_t *setup = &setup_command;

volatile uint8_t *setup_packet = usb_dpram->setup_packet;

static inline void prepare_setup_packet() {

    setup->direction = setup_packet[0] & PICO_TO_HOST_DIRECTION_MASK;
    setup->recipient = setup_packet[0] & USB_REQ_TYPE_RECIPIENT_MASK; 
    setup->request_type = setup_packet[0] & USB_REQ_TYPE_TYPE_MASK;
    
    setup->request = setup_packet[1];
    setup->descriptor_index = setup_packet[2];
    setup->descriptor_type = setup_packet[3];
    
    setup->value =  (setup_packet[3] << 8) | setup_packet[2];
    setup->index =  (setup_packet[5] << 8) | setup_packet[4];
    setup->length = (setup_packet[7] << 8) | setup_packet[6];
   
}

static inline void prepare_control_endpoints() {

    set_next_data_pid_to_host(0, USB_BUF_CTRL_DATA1_PID);
    set_next_data_pid_to_pico(0, USB_BUF_CTRL_DATA1_PID);
 
}

static inline void prepare_control_setup_direction() {

    if (setup->direction & PICO_TO_HOST_DIRECTION_MASK) {

        set_buffer_control_available_to_host(0, true);
        set_buffer_control_available_to_pico(0, false);

    } else {

        set_buffer_control_available_to_host(0, false);
        set_buffer_control_available_to_pico(0, true);

    }

}

void usb_handle_setup_packet() {
    
    prepare_setup_packet();

    prepare_control_endpoints();

    prepare_control_setup_direction();

    switch (setup->request_type) {

        case USB_REQ_TYPE_STANDARD:         usb_setup_type_standard();      break;
        case USB_REQ_TYPE_TYPE_CLASS:       usb_setup_type_class();         break;
        case USB_REQ_TYPE_TYPE_VENDOR:      usb_setup_type_unknown();       break;
        default:                            usb_setup_type_unknown();       break;
    }
}

static inline void usb_setup_type_unknown() {

    usb_error(USB_ERROR_LEVEL_ERROR);

    send_zlp_to_host(0);

}