/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stdio.h"
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/regs/usb.h"
#include "hardware/structs/usb.h"
#include "include/USB_buffer_completion.h"
#include "include/USB_setup_packet.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoints_host.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_uart_printf.h"
#include "include/USB_interrupts.h"
#include "include/USB_bus_reset.h"
#include "include/USB_sie_status.h"
#include "include/USB_sie_errors.h"

io_rw_32 USB_INTS = 0;

irq_handler_t __not_in_flash_func(isr_usbctrl)() {           // USB interrupt handler IRQ5

  USB_INTS = usb_hw->ints;
 
  if (USB_INTS & USB_INTS_BUFF_STATUS_BITS) {

    usb_irq_buffer_status();

  } else if (USB_INTS & USB_INTS_SETUP_REQ_BITS) {

    usb_irq_setup_request(); 
    
  } else if (USB_INTS & USB_INTS_BUS_RESET_BITS) {

    usb_irq_bus_reset(); 

  } else if (USB_INTS & USB_INTS_SIE_RECEIVE_ERRORS) {

    sie_status_receive_error_handler();

  } else if (USB_INTS & USB_INTS_ALL_OTHER_EVENTS) {

    sie_status_other_event_handler();

  } else {
    
    usb_irq_unhandled();

  }

}

static inline void __not_in_flash_func(usb_irq_buffer_status)() {

  if (USB_INTS & USB_INTS_ERROR_DATA_SEQ_BITS) {

    sie_status_data_sequence_error();

  }

  usb_handle_buffer_status();

}

static inline void usb_irq_setup_request() {

  usb_hardware_clear->sie_status = USB_SIE_STATUS_SETUP_REC_BITS; // must clear IRQ before servicing setup

  uart_printf(SEPARATOR);

  usb_handle_setup_packet();

}

static inline void usb_irq_bus_reset() {

  uart_printf("USB Bus Reset command received from host, function=%s\n\r", __func__);
   
  usb_hardware_clear->sie_status = USB_SIE_STATUS_BUS_RESET_BITS;

  disable_setup_interrupts();
      
  usb_handle_bus_reset();

  enable_setup_interrupts();

  enable_buffer_interrupts();

}

static inline void usb_irq_unhandled() {

  uart_printf(SEPARATOR);
  uart_printf("USB Unhandled IRQ received, IRQ=%08x, buffer=%08X, SIE=%08X\n\r", 
  USB_INTS, usb_hw->buf_status, usb_hw->sie_status);

  busy_wait_ms(1000);

}

void enable_setup_interrupts() {

  usb_hardware_set->inte = USB_INTS_SETUP_REQ_BITS;
  usb_hardware_set->inte = USB_INTS_ERROR_DATA_SEQ_BITS;

  uart_printf("Enabling Setup Request Interrupts\n\r");

}

void disable_setup_interrupts() {

  usb_hardware_clear->inte = USB_INTS_SETUP_REQ_BITS;
  usb_hardware_clear->inte = USB_INTS_ERROR_DATA_SEQ_BITS;

  uart_printf("Disabling Setup Request Interrupts\n\r");
  
}

void enable_buffer_interrupts() {

  usb_hardware_set->inte = USB_INTS_BUFF_STATUS_BITS;

  usb_hardware_set->sie_ctrl = USB_SIE_CTRL_EP0_INT_1BUF_BITS;
   
  uart_printf("Enabling Buffer Completion Interrupts\n\r");

}

void disable_buffer_interrupts() {

  usb_hardware_clear->inte = USB_INTS_BUFF_STATUS_BITS;
  
  uart_printf("Disabling Buffer Completion Interrupts\n\r");

}
