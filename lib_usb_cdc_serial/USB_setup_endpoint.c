/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/regs/usb.h"
#include "hardware/structs/usb.h"
#include "include/USB_error.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_device.h"
#include "include/USB_setup_packet.h"
#include "include/USB_setup_endpoint.h"
#include "include/USB_endpoint_struct.h"

void usb_setup_endpoint() {

    setup->direction ? setup_endpoint_respond_to_host() : setup_endpoint_request_to_pico();
 
}

static inline void setup_endpoint_respond_to_host() {

    setup_endpoint_request_unknown(); 

}

static inline void setup_endpoint_request_to_pico() {
 
    switch (setup->request) {
  
        case USB_REQUEST_CLEAR_FEATURE:     setup_endpoint_clear_feature(setup->index);     break;       
        case USB_REQUEST_SET_FEATURE:       setup_endpoint_request_unknown();               break;           
       
        default:                            setup_endpoint_request_unknown();               break;                   

    }

}

static inline void setup_endpoint_clear_feature(uint8_t ENDPOINT) {

    uint32_t stall_status_bit = 0;
    uint8_t EP_NUMBER = ENDPOINT & 0x7F;
    bool EP_DIRECTION = ENDPOINT & 0x80;
   
    if (EP_DIRECTION) {

        host_endpoint[EP_NUMBER].next_packet_id = USB_BUF_CTRL_DATA0_PID;

        usb_dpram->ep_buf_ctrl[EP_NUMBER].in &= ~USB_BUF_CTRL_STALL;
  
        stall_status_bit = 1u << ((2 * EP_NUMBER) + buffer_direction_to_host);

    } else {

        pico_endpoint[EP_NUMBER].next_packet_id = USB_BUF_CTRL_DATA0_PID;

        usb_dpram->ep_buf_ctrl[EP_NUMBER].out &= ~USB_BUF_CTRL_STALL;

        stall_status_bit = 1u << ((2 * EP_NUMBER) + buffer_direction_to_pico);

    }

    usb_hw->ep_nak_stall_status |= stall_status_bit;

}

static inline void setup_endpoint_request_unknown() {

    usb_error(USB_ERROR_LEVEL_ERROR);

    send_zlp_to_host(0);

}