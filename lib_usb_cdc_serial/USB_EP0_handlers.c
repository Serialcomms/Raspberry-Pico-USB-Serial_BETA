/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "pico/stdlib.h"
#include "pico/util/queue.h"
#include "hardware/irq.h"
#include "hardware/structs/usb.h" 
#include "include/USB_buffer_control.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_EP0_handlers.h"
#include "include/USB_data_packet.h" 
#include "include/USB_setup_control.h" 
#include "include/USB_queue_runner.h"
#include "include/USB_queue_control.h" 
#include "include/USB_queue_receive.h"
#include "include/USB_queue_transmit.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoint_control.h"

irq_handler_t ep0_handler_to_host(uint8_t EP_NUMBER) {

  clear_buffer_status(USB_BUFF_STATUS_EP0_IN_BITS); 

  toggle_next_data_pid_to_host(0);

  uint16_t bytes_remaining = get_queue_level_to_host(0); 

  if (bytes_remaining) {

    start_queue_runner_to_host(0);

  } else {

    end_pico_to_host_control_transfer();
  
  }

}  

irq_handler_t ep0_handler_to_pico(uint8_t EP_NUMBER) {

  clear_buffer_status(USB_BUFF_STATUS_EP0_OUT_BITS); 

  toggle_next_data_pid_to_pico(0);

  pico_endpoint[0].transfer_bytes = get_buffer_control_transfer_bytes_to_pico(0);

  if (get_pico_callback_handler(0)) run_pico_callback_handler();

}

static inline void run_pico_callback_handler() {

  void *buffer = get_host_endpoint_dpram_address(0);

  uint16_t transfer_bytes = pico_endpoint[0].transfer_bytes;

  endpoint_callback_handler pico_callback = get_pico_callback_handler(0);

  pico_callback(buffer, transfer_bytes);

  set_pico_callback_handler(0, NULL);

}

static inline void clear_buffer_status (uint32_t buffer_mask) {

  usb_hardware_clear->buf_status = buffer_mask;
 
}