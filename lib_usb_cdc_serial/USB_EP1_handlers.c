/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/structs/usb.h" 
#include "hardware/regs/usb.h" 
#include "include/USB_error.h"    
#include "include/USB_data_packet.h"  
#include "include/USB_queue_transmit.h"
#include "include/USB_queue_receive.h"
#include "include/USB_queue_builder.h"
#include "include/USB_queue_runner.h"
#include "include/USB_queue_control.h"
#include "include/USB_setup_control.h"
#include "include/USB_buffer_control.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoint_control.h"
#include "include/USB_EP1_handlers.h"

#include "include/USB_vcp.h"

extern void (*chars_available_callback)(void*);
extern void *chars_available_param;

irq_handler_t __not_in_flash_func(ep1_handler_to_host)(uint8_t EP_NUMBER) {

  clear_buffer_status(USB_BUFF_STATUS_EP1_IN_BITS); 

  toggle_next_data_pid_to_host(1);

  uint8_t max_packet_size = get_host_endpoint_max_packet_size(1);
  uint16_t bytes_remaining = get_queue_level_to_host(1);
  uint16_t bytes_transferred = get_buffer_control_transfer_bytes_to_host(1);
 
  if (bytes_remaining) {

    start_queue_runner_to_host(1);

  } else {

    if (bytes_transferred == max_packet_size) {
        
      send_zlp_to_host(1);
        
    } else {
                
      set_endpoint_busy_to_host(1, false);

    }

  }

}

irq_handler_t __not_in_flash_func(ep1_handler_to_pico)(uint8_t EP_NUMBER) {

  clear_buffer_status(USB_BUFF_STATUS_EP1_OUT_BITS); 

  toggle_next_data_pid_to_pico(1);

  uint8_t *source_data = get_pico_endpoint_dpram_address(1);
  uint8_t max_packet_size = get_pico_endpoint_max_packet_size(1);
  uint16_t bytes_received = get_buffer_control_transfer_bytes_to_pico(1);
  
  if (bytes_received) {
    
    add_source_data_to_pico_queue(1, source_data, bytes_received);

    if (chars_available_callback) chars_available_callback(NULL);

    uint16_t queue_free = get_queue_free_to_pico(EP_NUMBER); 
     
    if (queue_free >= max_packet_size) {
      
      set_queue_long_to_pico(EP_NUMBER, false);

      start_async_receive_data_packet(EP_NUMBER, max_packet_size);

    } else {
      
      set_queue_long_to_pico(EP_NUMBER, true);

    }

  }

}

static inline void clear_buffer_status(uint32_t buffer_mask) {
  
  usb_hardware_clear->buf_status = buffer_mask;

}