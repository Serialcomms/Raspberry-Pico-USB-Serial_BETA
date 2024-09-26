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

int16_t start_queue_transfer_to_pico(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes) {
  
  int16_t queue_bytes;
  uint16_t queue_free;
 
  bool queue_full = pico_endpoint[EP_NUMBER].queue_full;
  bool queue_empty = queue_is_empty_to_pico(EP_NUMBER);

  if (queue_empty) {

      queue_bytes = PICO_ERROR_NO_DATA;
	    
  } else if (queue_full) {

    queue_bytes = copy_queue_bytes_to_pico_buffer(EP_NUMBER, pico_buffer, pico_buffer_bytes);
	  
	  queue_free = get_queue_free_to_pico(EP_NUMBER);
	  
	  if (queue_free > 64) {

		  pico_endpoint[EP_NUMBER].queue_full = false;
	  
		  start_async_receive_data_packet(EP_NUMBER, 64);

		} 
	    
  } else {

    queue_bytes = copy_queue_bytes_to_pico_buffer(EP_NUMBER, pico_buffer, pico_buffer_bytes);

  }

  return queue_bytes;

}

int16_t copy_queue_bytes_to_pico_buffer(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes) {

  bool byte_removed = false;
  uint8_t QUEUE_BYTE;
  uint16_t buffer_offset = 0;
  int16_t bytes_sent = PICO_ERROR_NO_DATA;
  uint8_t *stdin_buffer_bytes = pico_buffer;

  do {

    byte_removed = queue_try_remove_to_pico(EP_NUMBER, &QUEUE_BYTE);

    if (byte_removed) {

      stdin_buffer_bytes[buffer_offset] = QUEUE_BYTE;

      ++buffer_offset;

    }

  } while (byte_removed && buffer_offset < pico_buffer_bytes);

  if (buffer_offset) bytes_sent = buffer_offset;

  return bytes_sent;

}