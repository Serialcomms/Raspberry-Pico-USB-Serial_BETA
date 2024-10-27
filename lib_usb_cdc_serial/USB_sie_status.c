/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/structs/usb.h"
#include "include/USB_error.h"
#include "include/USB_suspend_resume.h"
#include "include/USB_sie_status.h"

void sie_status_other_event_handler() {

    io_rw_32 sie_status = usb_hw->sie_status;

    if (sie_status & USB_SIE_STATUS_ACK_REC_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_ACK_REC_BITS;

        usb_error(USB_ERROR_LEVEL_WARN);

    }  
  
    if (sie_status & USB_SIE_STATUS_STALL_REC_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_STALL_REC_BITS;

        usb_error(USB_ERROR_LEVEL_WARN);

    }  

    if (sie_status & USB_SIE_STATUS_NAK_REC_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_NAK_REC_BITS;

        usb_error(USB_ERROR_LEVEL_WARN);

    }  

    if (sie_status & USB_SIE_STATUS_TRANS_COMPLETE_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_TRANS_COMPLETE_BITS;

        usb_error(USB_ERROR_LEVEL_WARN);

    }  

    if (sie_status & USB_SIE_STATUS_CONNECTED_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_CONNECTED_BITS;

        usb_error(USB_ERROR_LEVEL_WARN);

    } 

 //   if (sie_status & USB_SIE_STATUS_RESUME_BITS) {

  //      usb_hardware_clear->sie_status = USB_SIE_STATUS_RESUME_BITS;

  //      usb_error(USB_ERROR_LEVEL_WARN);

 //   } 
    
    if (sie_status & USB_SIE_STATUS_VBUS_OVER_CURR_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_VBUS_OVER_CURR_BITS;

        usb_error(USB_ERROR_LEVEL_WARN);

    }

    if (sie_status & USB_SIE_STATUS_VBUS_DETECTED_BITS) {

        usb_hardware_clear->sie_status = USB_SIE_STATUS_VBUS_DETECTED_BITS;

        usb_error(USB_ERROR_LEVEL_WARN);

    }

}