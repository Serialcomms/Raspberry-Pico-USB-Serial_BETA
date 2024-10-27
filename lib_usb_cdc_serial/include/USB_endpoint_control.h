/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

void __not_in_flash_func(*get_host_endpoint_handler)(uint8_t EP_NUMBER);
void __not_in_flash_func(*get_pico_endpoint_handler)(uint8_t EP_NUMBER);

void __not_in_flash_func(*get_host_callback_handler)(uint8_t EP_NUMBER);
void __not_in_flash_func(*get_pico_callback_handler)(uint8_t EP_NUMBER);

void __not_in_flash_func(*get_host_endpoint_dpram_address)(uint8_t EP_NUMBER);
void __not_in_flash_func(*get_pico_endpoint_dpram_address)(uint8_t EP_NUMBER);

bool __not_in_flash_func(get_endpoint_busy_to_host)(uint8_t EP_NUMBER);
bool __not_in_flash_func(get_endpoint_busy_to_pico)(uint8_t EP_NUMBER);

void __not_in_flash_func(set_endpoint_busy_to_host)(uint8_t EP_NUMBER, bool ep_busy);
void __not_in_flash_func(set_endpoint_busy_to_pico)(uint8_t EP_NUMBER, bool ep_busy);

bool __not_in_flash_func(get_endpoint_idle_to_host)(uint8_t EP_NUMBER);
bool __not_in_flash_func(get_endpoint_idle_to_pico)(uint8_t EP_NUMBER);

uint8_t __not_in_flash_func(get_host_endpoint_transfer_type)(uint8_t EP_NUMBER);
uint8_t __not_in_flash_func(get_pico_endpoint_transfer_type)(uint8_t EP_NUMBER);

uint16_t __not_in_flash_func(get_host_endpoint_max_packet_size)(uint8_t EP_NUMBER);
uint16_t __not_in_flash_func(get_pico_endpoint_max_packet_size)(uint8_t EP_NUMBER);

void set_host_endpoint_handler(uint8_t EP_NUMBER, void *endpoint_handler);
void set_pico_endpoint_handler(uint8_t EP_NUMBER, void *endpoint_handler);

void set_host_callback_handler(uint8_t EP_NUMBER, void *callback_handler);
void set_pico_callback_handler(uint8_t EP_NUMBER, void *callback_handler);