/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/structs/usb.h" 
#include "hardware/regs/usb.h"    
#include "include/USB_data_packet.h"  
#include "include/USB_debug_show.h"
#include "include/USB_queue_transmit.h"
#include "include/USB_queue_receive.h"
#include "include/USB_queue_control.h"
#include "include/USB_buffer_control.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_EP2_handlers.h"

#include "include/USB_vcp.h"
#include "include/USB_com_port_signalling.h"
#include "include/USB_uart_printf.h"

extern void (*chars_available_callback)(void*);
extern void *chars_available_param;

void __not_in_flash_func(ep2_handler_to_host)(uint8_t EP_NUMBER) {

  clear_buffer_status(USB_BUFF_STATUS_EP2_IN_BITS); 

  toggle_next_data_pid_to_host(2);

  uint16_t bytes_remaining = get_queue_level_to_host(2);

  if (bytes_remaining) {

    ep2_queue_runner_to_host();

  } else {

    set_queue_busy_to_host(2, false);

  }

}

static inline void __not_in_flash_func (ep2_queue_runner_to_host()) {

  bool queue_remove_result;
  uint8_t source_data_byte;
  uint16_t source_data_offset = 0;
  uint8_t *endpoint_buffer = host_endpoint[2].dpram_address;

  do {

    queue_remove_result = queue_try_remove_to_host(2, &source_data_byte); 

    if (queue_remove_result) endpoint_buffer[source_data_offset++] = source_data_byte;
    
  } while (queue_remove_result && source_data_offset < host_endpoint[2].max_packet_size);

  if (source_data_offset) start_async_send_data_packet(2, source_data_offset);

}

void  __not_in_flash_func(ep2_handler_to_pico)(uint8_t EP_NUMBER) {

  clear_buffer_status(USB_BUFF_STATUS_EP2_OUT_BITS); 

  toggle_next_data_pid_to_pico(2);

  uint16_t bytes_received = get_buffer_control_transfer_bytes_to_pico(EP_NUMBER);

  pico_endpoint[2].transfer_bytes = bytes_received;

  uart_printf("----------------------------------------------------------------------------------------\n\r");

  uart_printf("EP%d handler to Pico, clearing buffer status, bytes=%d, PID=%d\n\r", 
  EP_NUMBER, bytes_received, get_last_data_pid_to_pico(2));
  
  if (bytes_received) {

    show_character_to_pico(EP_NUMBER);
    
    add_ep2_data_to_queue(bytes_received);

    if (chars_available_callback) chars_available_callback(NULL);

    uint16_t queue_free = get_queue_free_to_pico(EP_NUMBER); 
     
    if (queue_free > 64) {

      pico_endpoint[EP_NUMBER].queue_full = false;
	  
      start_async_receive_data_packet(EP_NUMBER, 64);

    } else {
      
      pico_endpoint[EP_NUMBER].queue_full = true;

    }

  }

}

void  __not_in_flash_func(add_ep2_data_to_queue)(uint16_t source_data_length) {

  bool queue_add_result;

  uint16_t source_data_offset = 0;

  uint8_t *source_data = pico_endpoint[2].dpram_address;

  bool queue_capacity = queue_wait_for_capacity_to_host(2, source_data_length, 5000);

  if (queue_capacity)  {

    do {

      queue_add_result = queue_try_add_to_pico(2, &source_data[source_data_offset]); 

      if (queue_add_result) ++source_data_offset;

    } while (queue_add_result && source_data_offset < source_data_length);

  uart_printf("EP%d handler to Pico, Add Data to Queue, bytes=%d, level=%d, offset=%d\n\r", 
  2, source_data_length, get_queue_level_to_pico(2), source_data_offset);

  } else {

    uint16_t queue_free_length = get_queue_free_to_pico(2);
    
    uart_printf("ERROR - insufficient receive queue space, required=%d, available=%d\n\r", 
    source_data_length, queue_free_length);

  }

}

static inline void clear_buffer_status(uint32_t buffer_mask) {
  
  usb_hardware_clear->buf_status = buffer_mask;

}

static inline void show_dpram_to_pico(uint8_t EP_NUMBER) {

  show_dpram(EP_NUMBER, pico_endpoint[EP_NUMBER].dpram_address);

}

static inline void show_dpram_to_host(uint8_t EP_NUMBER) {

  show_dpram(EP_NUMBER, host_endpoint[EP_NUMBER].dpram_address);

}

static inline void show_character_to_host(uint8_t EP_NUMBER) {

  uint8_t *usb_dpram_data = host_endpoint[EP_NUMBER].dpram_address;

  uart_printf("Character Sent = (%02X), %c \n\r", usb_dpram_data[0], usb_dpram_data[0]);

}

static inline void show_character_to_pico(uint8_t EP_NUMBER) {

  uint8_t *usb_dpram_data = pico_endpoint[EP_NUMBER].dpram_address;

  uint8_t CHARACTER = usb_dpram_data[0];

  if (CHARACTER == 'R') com_port_set_ring(true);
  if (CHARACTER == 'r') com_port_set_ring(false);

  if (CHARACTER == 'D') com_port_set_dcd(true);
  if (CHARACTER == 'd') com_port_set_dcd(false);

  if (CHARACTER == 'S') com_port_set_dsr(true);
  if (CHARACTER == 's') com_port_set_dsr(false);

  if (CHARACTER < 32) CHARACTER = ' ';

  uart_printf("Character Received = (%02X), %c \n\r", usb_dpram_data[0], CHARACTER);

}