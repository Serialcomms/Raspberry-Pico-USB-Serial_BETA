/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/structs/usb.h"
#include "include/USB_uart_printf.h"
#include "include/USB_sie_status.h"

void sie_status_other_event_handler() {

    io_rw_32 sie_status = usb_hw->sie_status;

    if (sie_status & USB_SIE_STATUS_ACK_REC_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_ACK_REC_BITS;

        uart_printf("Serial Interface Engine, ACK Received, Register=%08x \n\r", sie_status);

    }  
  
    if (sie_status & USB_SIE_STATUS_STALL_REC_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_STALL_REC_BITS;

        uart_printf("Serial Interface Engine, Stall Received, Register=%08x \n\r", sie_status);

    }  

    if (sie_status & USB_SIE_STATUS_NAK_REC_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_NAK_REC_BITS;

        uart_printf("Serial Interface Engine, NAK Received, Register=%08x \n\r", sie_status);

    }  

    if (sie_status & USB_SIE_STATUS_TRANS_COMPLETE_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_TRANS_COMPLETE_BITS;

        uart_printf("Serial Interface Engine, Transaction Complete, Register=%08x \n\r", sie_status);

    }  

    if (sie_status & USB_SIE_STATUS_CONNECTED_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_CONNECTED_BITS;

        uart_printf("Serial Interface Engine, Device Connected, Register=%08x \n\r", sie_status);

    } 

    if (sie_status & USB_SIE_STATUS_RESUME_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_RESUME_BITS;

        uart_printf("Serial Interface Engine, Host Resume, Register=%08x \n\r", sie_status);

    } 
    
    if (sie_status & USB_SIE_STATUS_VBUS_OVER_CURR_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_VBUS_OVER_CURR_BITS;

        uart_printf("Serial Interface Engine, VBUS Over Current, Register=%08x \n\r", sie_status);

    }

    if (sie_status & USB_SIE_STATUS_VBUS_DETECTED_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_VBUS_DETECTED_BITS;

        uart_printf("Serial Interface Engine, VBUS Detected, Register=%08x \n\r", sie_status);

    }

}