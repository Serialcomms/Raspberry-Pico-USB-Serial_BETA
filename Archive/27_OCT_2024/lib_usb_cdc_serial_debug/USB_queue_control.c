/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_queue_control.h"

void set_queue_busy_to_host(uint8_t EP_NUMBER, bool busy_state) {

  host_endpoint[EP_NUMBER].queue_busy = busy_state;

}

bool get_queue_busy_to_host(uint8_t EP_NUMBER) {

  return host_endpoint[EP_NUMBER].queue_busy;

}

void set_queue_long_to_host(uint8_t EP_NUMBER, bool queue_long) {

  host_endpoint[EP_NUMBER].queue_long = queue_long;

}

void set_queue_long_to_pico(uint8_t EP_NUMBER, bool queue_long) {

  pico_endpoint[EP_NUMBER].queue_long = queue_long;

}

bool get_queue_long_to_host(uint8_t EP_NUMBER) {

  return host_endpoint[EP_NUMBER].queue_long;

}

bool get_queue_long_to_pico(uint8_t EP_NUMBER) {

  return pico_endpoint[EP_NUMBER].queue_long;

}

uint16_t get_queue_level_to_host(uint8_t EP_NUMBER) {

  return queue_get_level(&host_endpoint[EP_NUMBER].data_queue);

}

uint16_t get_queue_free_to_host(uint8_t EP_NUMBER) {

  return host_endpoint[EP_NUMBER].data_queue.element_count - get_queue_level_to_host(EP_NUMBER);

}

bool queue_is_empty_to_host(uint8_t EP_NUMBER) {

  return queue_is_empty(&host_endpoint[EP_NUMBER].data_queue);

}

bool queue_try_add_to_host(uint8_t EP_NUMBER, const uint8_t *source_data_byte) {

  return queue_try_add(&host_endpoint[EP_NUMBER].data_queue, source_data_byte);

}

bool queue_try_remove_to_host(uint8_t EP_NUMBER, void *source_data_byte) {

  return queue_try_remove(&host_endpoint[EP_NUMBER].data_queue, source_data_byte);

}

void set_queue_busy_to_pico(uint8_t EP_NUMBER, bool busy_state) {

  pico_endpoint[EP_NUMBER].queue_busy = busy_state;

}

bool get_queue_busy_to_pico(uint8_t EP_NUMBER) {

  return pico_endpoint[EP_NUMBER].queue_busy;

}

uint16_t get_queue_level_to_pico(uint8_t EP_NUMBER) {

  return queue_get_level(&pico_endpoint[EP_NUMBER].data_queue);

}

uint16_t get_queue_free_to_pico(uint8_t EP_NUMBER) {

  return pico_endpoint[EP_NUMBER].data_queue.element_count - get_queue_level_to_pico(EP_NUMBER);

}

bool queue_is_empty_to_pico(uint8_t EP_NUMBER) {

  return queue_is_empty(&pico_endpoint[EP_NUMBER].data_queue);

}

bool queue_try_add_to_pico(uint8_t EP_NUMBER, const uint8_t *source_data_byte) {

  return queue_try_add(&pico_endpoint[EP_NUMBER].data_queue, source_data_byte);

}

bool queue_try_remove_to_pico(uint8_t EP_NUMBER, void *source_data_byte) {

  return queue_try_remove(&pico_endpoint[EP_NUMBER].data_queue, source_data_byte);

}

void queue_remove_blocking_to_pico(uint8_t EP_NUMBER, void *source_data_byte) {

  queue_remove_blocking(&pico_endpoint[EP_NUMBER].data_queue, source_data_byte);

}

void queue_remove_blocking_to_host(uint8_t EP_NUMBER, void *source_data_byte) {

  queue_remove_blocking(&host_endpoint[EP_NUMBER].data_queue, source_data_byte);

}

bool wait_for_queue_capacity_to_host(uint8_t EP_NUMBER, uint16_t required_capacity, uint16_t wait_milliseconds) {

  bool wait_timeout;

  uint16_t queue_capacity  = get_queue_free_to_host(EP_NUMBER);
  
  if (queue_capacity >= required_capacity) {
    
    return true;

  } else {
	  
    absolute_time_t wait_time = make_timeout_time_ms(wait_milliseconds);

    do {
    
      wait_timeout = time_reached(wait_time);
    
      queue_capacity = get_queue_free_to_host(EP_NUMBER);

    } while (!wait_timeout && queue_capacity < required_capacity);
  
  }

  return !wait_timeout;

}