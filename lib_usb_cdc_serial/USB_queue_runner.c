/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_data_packet.h"
#include "include/USB_endpoint_control.h"
#include "include/USB_queue_control.h"
#include "include/USB_queue_runner.h"

int16_t __not_in_flash_func(dequeue_bytes_to_pico_buffer)(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes) {

  bool removed;
  uint8_t QUEUE_BYTE;
  uint16_t buffer_offset = 0;
  uint16_t bytes_removed = 0;
  uint8_t *pico_buffer_data = pico_buffer;

  do {

    removed = queue_try_remove_to_pico(EP_NUMBER, &QUEUE_BYTE);

    if (removed) {
      
      pico_buffer_data[buffer_offset] = QUEUE_BYTE;
      
      ++bytes_removed;
      
    }

  } while (removed && ++buffer_offset < pico_buffer_bytes);
  
  if (bytes_removed) {

    return bytes_removed;

  } else {

    return PICO_ERROR_NO_DATA;

  }

}

int16_t __not_in_flash_func(dequeue_bytes_to_host_buffer)(uint8_t EP_NUMBER, void *host_buffer, uint16_t host_buffer_bytes) {

  bool removed;
  uint8_t QUEUE_BYTE;
  uint16_t buffer_offset = 0;
  uint16_t bytes_removed = 0; 
  uint8_t *host_buffer_data = host_buffer;

  do {

    removed = queue_try_remove_to_host(EP_NUMBER, &QUEUE_BYTE); 

    if (removed) {
      
      host_buffer_data[buffer_offset] = QUEUE_BYTE;
      
      ++bytes_removed;
      
    }
   
  } while (removed && ++buffer_offset < host_buffer_bytes);

  return bytes_removed;

}

void __not_in_flash_func(start_queue_runner_to_host)(uint8_t EP_NUMBER) {

  void *host_buffer = get_host_endpoint_dpram_address(EP_NUMBER);

  uint8_t max_packet_size = get_host_endpoint_max_packet_size(EP_NUMBER);

  uint16_t queue_bytes = dequeue_bytes_to_host_buffer(EP_NUMBER, host_buffer, max_packet_size);

  if (queue_bytes) start_async_send_data_packet(EP_NUMBER, queue_bytes);

}