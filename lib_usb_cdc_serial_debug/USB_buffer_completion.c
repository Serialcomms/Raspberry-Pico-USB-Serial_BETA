/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stdio.h"
#include "pico/stdlib.h"
#include "hardware/structs/usb.h"
#include "include/USB_uart_printf.h"
#include "include/USB_buffer_control.h"
#include "include/USB_buffer_completion.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoints_host.h"
#include "include/USB_endpoints_pico.h"

void usb_handle_buffer_status() {

  uint8_t  endpoint_buffer_number = 0;
  io_rw_32 buffer_status_register = usb_hw->buf_status;
  uint32_t endpoint_buffer_status = buffer_status_register;

  do {

    if (endpoint_buffer_status & buffer_status_bit_host) {

      usb_handle_buffer_status_host(endpoint_buffer_number);
        
    }

    if (endpoint_buffer_status & buffer_status_bit_pico) {

      usb_handle_buffer_status_pico(endpoint_buffer_number);
        
    }

    endpoint_buffer_status >>= 2;

  } while (++endpoint_buffer_number < 16 && endpoint_buffer_status);
  
}

static inline void usb_handle_buffer_status_host(uint8_t EP_NUMBER) {

  void *handler_address = host_endpoint[EP_NUMBER].endpoint_handler;

  buffer_completion_handler buffer_completion_function = handler_address;

  if (handler_address) {

    buffer_completion_function(EP_NUMBER);

  } else {

    buffer_completion_default_host(EP_NUMBER);
  
  }

}

static inline void usb_handle_buffer_status_pico(uint8_t EP_NUMBER) {

  void *handler_address = pico_endpoint[EP_NUMBER].endpoint_handler;

  buffer_completion_handler buffer_completion_function = handler_address;

  if (handler_address) {

    buffer_completion_function(EP_NUMBER);

  } else {

    buffer_completion_default_pico(EP_NUMBER);
  
  }
}

static inline void buffer_completion_default_host(uint8_t EP_NUMBER) {

  uart_printf("Buffer Completion Default Handler, Pico to Host, EP=%d, Buffer Status=%08x, Bytes=%d\n\r", 
  EP_NUMBER, usb_hw->buf_status, get_buffer_control_transfer_bytes_to_host(EP_NUMBER));

  clear_buffer_status_to_host(EP_NUMBER);

  toggle_next_data_pid_to_host(EP_NUMBER);

}

static inline void buffer_completion_default_pico(uint8_t EP_NUMBER) {

  printf("Buffer Completion Default Handler, Host to Pico, EP=%d, Buffer Status=%08x, Bytes=%d\n\r", 
  EP_NUMBER, usb_hw->buf_status, get_buffer_control_transfer_bytes_to_pico(EP_NUMBER));

  clear_buffer_status_to_pico(EP_NUMBER);

  toggle_next_data_pid_to_pico(EP_NUMBER);

}

uint32_t get_buffer_mask_to_host(uint8_t EP_NUMBER) {

  uint32_t buffer_mask = 1u << ((2 * EP_NUMBER) + buffer_direction_to_host);

  return buffer_mask;

}

uint32_t get_buffer_mask_to_pico(uint8_t EP_NUMBER) {

  uint32_t buffer_mask = 1u << ((2 * EP_NUMBER) + buffer_direction_to_pico);
  
  return buffer_mask;

}

bool get_buffer_status_complete_to_host(uint8_t EP_NUMBER) {

  uint32_t buffer_status_bit = get_buffer_mask_to_host(EP_NUMBER);

  return usb_hw->buf_status & buffer_status_bit;

}

bool get_buffer_status_complete_to_pico(uint8_t EP_NUMBER) {

  uint32_t buffer_status_bit = get_buffer_mask_to_pico(EP_NUMBER);

  return usb_hw->buf_status & buffer_status_bit;

}

void clear_buffer_status_to_host(uint8_t EP_NUMBER) {

  uint32_t buffer_status_bit = get_buffer_mask_to_host(EP_NUMBER);

  usb_hardware_clear->buf_status = buffer_status_bit;

}

void clear_buffer_status_to_pico(uint8_t EP_NUMBER) {

  uint32_t buffer_status_bit = get_buffer_mask_to_pico(EP_NUMBER);

  usb_hardware_clear->buf_status = buffer_status_bit;

}