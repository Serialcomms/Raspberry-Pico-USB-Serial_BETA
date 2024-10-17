/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/regs/usb.h"              // USB register definitions
#include "hardware/structs/usb.h"           // USB hardware struct definitions
#include "include/USB_uart_printf.h"
#include "include/USB_bus_reset.h"
#include "include/USB_build_endpoints.h"

void usb_handle_bus_reset() {

  uart_printf("Processing USB Bus Reset command \n\r");

  reset_device_address();

  clear_usb_interrupts();

  clear_usb_start_of_frame();

  clear_sie_status_register();

  clear_buffer_status_register();

  usb_build_default_endpoints();

}

static inline void reset_device_address() {

  usb_hw->dev_addr_ctrl = 0;

}

static inline void clear_usb_start_of_frame() {

  uint32_t SOF_COUNT = usb_hw->sof_rd;

}

static inline void clear_usb_interrupts() {
  
  usb_hw->inte = ZERO_ALL_BITS;
  usb_hw->intf = ZERO_ALL_BITS;
  
}

static inline void clear_buffer_status_register() {

  usb_hardware_clear->buf_status = CLEAR_ALL_BITS;  

}

void clear_sie_status_register() {

  usb_hardware_clear->sie_status = USB_SIE_STATUS_BUS_RESET_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_DATA_SEQ_ERROR_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_ACK_REC_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_RX_TIMEOUT_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_RX_OVERFLOW_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_BIT_STUFF_ERROR_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_CRC_ERROR_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_TRANS_COMPLETE_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_SETUP_REC_BITS;
  usb_hardware_clear->sie_status = USB_SIE_STATUS_SUSPENDED_BITS;

}