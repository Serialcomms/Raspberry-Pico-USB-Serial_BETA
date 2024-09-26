/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "include/USB_setup_address.h"
#include "include/USB_data_packet.h"
#include "include/USB_queue_transmit.h"
#include "include/USB_queue_control.h"
#include "include/USB_buffer_control.h"
#include "include/USB_endpoints_host.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_uart_printf.h"
#include "include/USB_setup_control.h"

void start_control_transfer_to_host(const void *source_buffer_address, uint8_t source_buffer_length) {
  
  if (get_pico_device_address()) {

    set_queue_transfer_ack_to_host(0, true);

    start_queue_transfer_to_host(0, source_buffer_address, source_buffer_length);

  } else {

    memcpy(host_endpoint[0].dpram_address, source_buffer_address, source_buffer_length);

    start_async_send_data_packet(0, source_buffer_length);

    receive_zlp_from_host(0);

  }

}

void start_control_transfer_receive_callback(void (*callback)(uint8_t *data, uint8_t transfer_bytes), uint8_t expected_bytes) {

  uart_printf("Control Transfer Data Stage, Expected Bytes=%d\n\r", expected_bytes);
  
  set_pico_callback_handler(0, callback);

  start_async_receive_data_packet(0, expected_bytes);

}

void send_zlp_to_host(uint8_t EP_NUMBER) {

  set_queue_transfer_ack_to_host(EP_NUMBER, false);

  start_async_send_data_packet(EP_NUMBER, ZERO_LENGTH_PACKET);

}

void receive_zlp_from_host(uint8_t EP_NUMBER) {

  start_async_receive_data_packet(EP_NUMBER, ZERO_LENGTH_PACKET);

}

void end_pico_to_host_control_transfer() {

  if (host_endpoint[0].send_ack) {

    start_async_receive_data_packet(0, ZERO_LENGTH_PACKET);

  }

  set_queue_busy_to_host(0, false);

}

void set_queue_transfer_ack_to_host(uint8_t EP_NUMBER, bool state) {

  host_endpoint[EP_NUMBER].send_ack = state; 

}