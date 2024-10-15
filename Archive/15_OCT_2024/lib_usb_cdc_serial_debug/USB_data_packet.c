
/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_buffer_control.h"
#include "include/USB_data_packet.h"

void start_async_send_data_packet(uint8_t EP_NUMBER, uint8_t transfer_bytes) {

  uint32_t DATA_PID = get_next_data_pid_to_host(EP_NUMBER);

  uint32_t buffer_dispatch = DATA_PID | USB_BUFFER_CONTROL_FULL;

  set_buffer_control_dispatch_to_host(EP_NUMBER, buffer_dispatch);

  set_buffer_control_transfer_bytes_to_host(EP_NUMBER, transfer_bytes);
 
  busy_wait_at_least_cycles(3);

  set_buffer_control_available_to_host(EP_NUMBER, true);

}

void start_async_receive_data_packet(uint8_t EP_NUMBER, uint8_t transfer_bytes) {
     
  uint32_t DATA_PID = get_next_data_pid_to_pico(EP_NUMBER);

  uint32_t buffer_dispatch = DATA_PID;

  set_buffer_control_transfer_bytes_to_pico(EP_NUMBER, transfer_bytes);

  set_buffer_control_dispatch_to_pico(EP_NUMBER, buffer_dispatch);

  busy_wait_at_least_cycles(3);

  set_buffer_control_available_to_pico(EP_NUMBER, true);

}