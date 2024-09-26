/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/structs/usb.h"
#include "include/USB_error.h"
#include "include/USB_sie_errors.h"

void sie_status_data_sequence_error() {

  usb_error(USB_ERROR_LEVEL_ERROR);
  
  usb_hardware_clear->sie_status = USB_SIE_STATUS_DATA_SEQ_ERROR_BITS;

}

void sie_status_receive_error_handler() {

  io_rw_32 sie_errors = usb_hw->sie_status;

  if (sie_errors & USB_SIE_STATUS_RX_TIMEOUT_BITS) {

    usb_hardware_clear->sie_status = USB_SIE_STATUS_RX_TIMEOUT_BITS;

    usb_error(USB_ERROR_LEVEL_ERROR);

  }

  if (sie_errors & USB_SIE_STATUS_RX_OVERFLOW_BITS) {

    usb_hardware_clear->sie_status = USB_SIE_STATUS_RX_OVERFLOW_BITS;

    usb_error(USB_ERROR_LEVEL_ERROR);

  }
        
  if (sie_errors & USB_SIE_STATUS_BIT_STUFF_ERROR_BITS) {

    usb_hardware_clear->sie_status = USB_SIE_STATUS_BIT_STUFF_ERROR_BITS;

    usb_error(USB_ERROR_LEVEL_ERROR);

  }

  if (sie_errors & USB_SIE_STATUS_CRC_ERROR_BITS) {

    usb_hardware_clear->sie_status = USB_SIE_STATUS_CRC_ERROR_BITS;

    usb_error(USB_ERROR_LEVEL_ERROR);

  }

}