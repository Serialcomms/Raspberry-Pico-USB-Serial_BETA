/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/util/queue.h"
#include "hardware/structs/usb.h" 
#include "include/USB_buffer_control.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_EP0_handlers.h"
#include "include/USB_data_packet.h" 
#include "include/USB_setup_control.h" 
#include "include/USB_queue_control.h" 
#include "include/USB_queue_receive.h"
#include "include/USB_queue_transmit.h"
#include "include/USB_endpoint_struct.h"

void ep0_handler_to_host(uint8_t EP_NUMBER) {

  clear_buffer_status(USB_BUFF_STATUS_EP0_IN_BITS); 

  toggle_next_data_pid_to_host(0);

  uint16_t bytes_remaining = get_queue_level_to_host(0); 

  if (bytes_remaining) {

    ep0_queue_runner_to_host();

  } else {

    end_pico_to_host_control_transfer();
  
  }

}  

static inline void ep0_queue_runner_to_host() {

  bool queue_remove_result;
  uint8_t source_data_byte;
  uint16_t source_data_offset = 0;
  uint8_t *endpoint_buffer = host_endpoint[0].dpram_address;

  do {

    queue_remove_result = queue_try_remove_to_host(0, &source_data_byte); 

    if (queue_remove_result) endpoint_buffer[source_data_offset++] = source_data_byte;
    
  } while (queue_remove_result && source_data_offset < host_endpoint[0].max_packet_size);

  if (source_data_offset) start_async_send_data_packet(0, source_data_offset);

}

void ep0_handler_to_pico(uint8_t EP_NUMBER) {

  clear_buffer_status(USB_BUFF_STATUS_EP0_OUT_BITS); 

  toggle_next_data_pid_to_pico(0);

  pico_endpoint[0].transfer_bytes = get_buffer_control_transfer_bytes_to_pico(0);

  if (get_pico_callback_handler(0)) run_pico_callback_handler();

}

static inline void run_pico_callback_handler() {

  void* buffer = pico_endpoint[0].dpram_address;

  uint16_t transfer_bytes = pico_endpoint[0].transfer_bytes;

  endpoint_callback_handler pico_callback = get_pico_callback_handler(0);

  pico_callback(buffer, transfer_bytes);

  set_pico_callback_handler(0, NULL);

}

static inline void clear_buffer_status (uint32_t buffer_mask) {

  usb_hardware_clear->buf_status = buffer_mask;
 
}