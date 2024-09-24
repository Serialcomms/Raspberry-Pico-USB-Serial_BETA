/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/util/queue.h"
#include "include/USB_uart_printf.h"
#include "include/USB_data_packet.h"
#include "include/USB_queue_control.h"
#include "include/USB_queue_transmit.h"
#include "include/USB_endpoint_struct.h"

void start_queue_transfer_to_host(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {

  bool queue_capacity = queue_wait_for_capacity_to_host(EP_NUMBER, source_data_length, 5000);
  
  if (queue_capacity) {

    prepare_queue_transfer_to_host(EP_NUMBER, source_data, source_data_length); 

  } else {

    uart_printf("ERROR - insufficient transmit queue space, required=%d, available=%d\n\r", 
    source_data_length, get_queue_free_to_host(EP_NUMBER));
   
  }
 
}

static inline void prepare_queue_transfer_to_host(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {

  bool queue_busy = get_queue_busy_to_host(EP_NUMBER);
   
  if (queue_busy) {

    queue_try_extend_transfer_to_host(EP_NUMBER, source_data, source_data_length);  

  } else {

    set_queue_busy_to_host(EP_NUMBER, true);
    
    build_queue_transfer_to_host(EP_NUMBER, source_data, source_data_length);

    uint16_t data_bytes = build_first_packet_to_host(EP_NUMBER);
    
    start_async_send_data_packet(EP_NUMBER, data_bytes);

  }

}

static inline void build_queue_transfer_to_host(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {

  bool queue_add_result = false;
  uint16_t source_data_offset = 0;

  do {

    queue_add_result = queue_try_add_to_host(EP_NUMBER, &source_data[source_data_offset]);

    if (queue_add_result) ++source_data_offset;

  } while (queue_add_result && source_data_offset < source_data_length);

}

static inline uint16_t build_first_packet_to_host(uint8_t EP_NUMBER) {

  bool queue_remove_result;
  uint8_t source_data_byte;
  uint16_t source_data_offset = 0;
  uint8_t *endpoint_buffer = host_endpoint[EP_NUMBER].dpram_address;
  uint16_t max_packet_size = host_endpoint[EP_NUMBER].max_packet_size; 
  
  do {

    queue_remove_result = queue_try_remove_to_host(EP_NUMBER, &source_data_byte); 

    if (queue_remove_result) endpoint_buffer[source_data_offset++] = source_data_byte;

  } while (queue_remove_result && source_data_offset < max_packet_size);

  return source_data_offset;

}

static inline void queue_try_extend_transfer_to_host(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {

  uint32_t ENDPOINT_TRANSFER_TYPE = host_endpoint[EP_NUMBER].transfer_type;

  if (ENDPOINT_TRANSFER_TYPE == USB_TRANSFER_TYPE_BULK) {

    build_queue_transfer_to_host(EP_NUMBER, source_data, source_data_length);    

  } else {

    uart_printf("ERROR - Cannot extend active transfer queue for Endpoint Type=%d\n\r", host_endpoint[EP_NUMBER].transfer_type);

  }

}

