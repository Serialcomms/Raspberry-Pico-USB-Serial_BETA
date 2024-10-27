/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_data_packet.h"
#include "include/USB_queue_control.h"
#include "include/USB_queue_receive.h"

int16_t __not_in_flash_func(start_queue_transfer_to_pico)(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes) {
  
  int16_t queue_bytes;
  uint16_t queue_free;
 
  bool queue_long = get_queue_long_to_pico(EP_NUMBER);
  bool queue_empty = queue_is_empty_to_pico(EP_NUMBER);
 
  set_queue_busy_to_pico(EP_NUMBER, true);

  if (queue_empty) {

    queue_bytes = PICO_ERROR_NO_DATA;
	    
  } else if (queue_long) {

    queue_bytes = copy_queue_bytes_to_pico_buffer(EP_NUMBER, pico_buffer, pico_buffer_bytes);
    
    queue_free = get_queue_free_to_pico(EP_NUMBER);
    
    if (queue_free > 63) {
      
      set_queue_long_to_pico(EP_NUMBER, false);
      
      start_async_receive_data_packet(EP_NUMBER, 64);
      
    } 
	    
  } else {

    queue_bytes = copy_queue_bytes_to_pico_buffer(EP_NUMBER, pico_buffer, pico_buffer_bytes);

  }

  set_queue_busy_to_pico(EP_NUMBER, false);

  return queue_bytes;

}

int16_t __not_in_flash_func(copy_queue_bytes_to_pico_buffer)(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes) {

  bool byte_removed = false;
  uint8_t QUEUE_BYTE;
  uint16_t buffer_offset = 0;
  uint16_t source_data_count = 0;
  int16_t bytes_sent = PICO_ERROR_NO_DATA;
  uint8_t *stdin_buffer_bytes = pico_buffer;

  do {

    byte_removed = queue_try_remove_to_pico(EP_NUMBER, &QUEUE_BYTE);

    if (byte_removed) {
      
      stdin_buffer_bytes[buffer_offset] = QUEUE_BYTE;
      
      ++source_data_count;
      
    }

  } while (byte_removed && ++buffer_offset < pico_buffer_bytes);
  
  if (source_data_count) bytes_sent = source_data_count;

  return bytes_sent;

}