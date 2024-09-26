/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

uint32_t get_last_data_pid_to_pico(uint8_t EP_NUMBER);
uint32_t get_last_data_pid_to_host(uint8_t EP_NUMBER);

uint32_t get_next_data_pid_to_pico(uint8_t EP_NUMBER);
uint32_t get_next_data_pid_to_host(uint8_t EP_NUMBER);

void toggle_next_data_pid_to_pico(uint8_t EP_NUMBER);
void toggle_next_data_pid_to_host(uint8_t EP_NUMBER);

void set_next_data_pid_to_pico(uint8_t EP_NUMBER, uint32_t data_pid);
void set_next_data_pid_to_host(uint8_t EP_NUMBER, uint32_t data_pid);

void set_buffer_control_available_to_pico(uint8_t EP_NUMBER, bool AVAILABLE);
void set_buffer_control_available_to_host(uint8_t EP_NUMBER, bool AVAILABLE);

void set_buffer_control_dispatch_to_pico(uint8_t EP_NUMBER, uint32_t buffer_dispatch);
void set_buffer_control_dispatch_to_host(uint8_t EP_NUMBER, uint32_t buffer_dispatch);

void set_buffer_control_transfer_bytes_to_pico(uint8_t EP_NUMBER, uint16_t buffer_bytes);
void set_buffer_control_transfer_bytes_to_host(uint8_t EP_NUMBER, uint16_t buffer_bytes);

uint32_t get_buffer_control_transfer_bytes_to_pico(uint8_t EP_NUMBER);
uint32_t get_buffer_control_transfer_bytes_to_host(uint8_t EP_NUMBER);