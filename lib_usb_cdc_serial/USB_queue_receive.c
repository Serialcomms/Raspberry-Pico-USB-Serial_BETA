/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

#include "include/USB_data_packet.h"
#include "include/USB_queue_runner.h"
#include "include/USB_queue_control.h"
#include "include/USB_queue_receive.h"
#include "include/USB_endpoint_control.h"

int16_t __not_in_flash_func(start_queue_transfer_to_pico)(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes) {
  
  int16_t queue_bytes;
  uint16_t queue_free;
 
  bool queue_long = get_queue_long_to_pico(EP_NUMBER);
  bool queue_empty = queue_is_empty_to_pico(EP_NUMBER);
  uint8_t max_packet_size = get_pico_endpoint_max_packet_size(EP_NUMBER);
 
  set_queue_busy_to_pico(EP_NUMBER, true);

  if (queue_empty) {

    queue_bytes = PICO_ERROR_NO_DATA;

  } else {

    queue_bytes = dequeue_bytes_to_pico_buffer(EP_NUMBER, pico_buffer, pico_buffer_bytes);

    if (queue_long) {

      queue_free = get_queue_free_to_pico(EP_NUMBER);
    
      if (queue_free >= max_packet_size) {
      
        set_queue_long_to_pico(EP_NUMBER, false);
      
        start_async_receive_data_packet(EP_NUMBER, max_packet_size);
      
      } 

    }  
 
  }
	    
  set_queue_busy_to_pico(EP_NUMBER, false);

  return queue_bytes;

}
