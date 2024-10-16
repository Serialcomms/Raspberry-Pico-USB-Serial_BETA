/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoint_control.h"

void *get_host_endpoint_handler(uint8_t EP_NUMBER) {
    
    return host_endpoint[EP_NUMBER].endpoint_handler;
}

void set_host_endpoint_handler(uint8_t EP_NUMBER, void *endpoint_handler) {
    
    host_endpoint[EP_NUMBER].endpoint_handler = endpoint_handler;
}

void *get_host_callback_handler(uint8_t EP_NUMBER) {
    
    return host_endpoint[EP_NUMBER].callback_handler;
}

void *get_host_endpoint_dpram_address(uint8_t EP_NUMBER) {

    return host_endpoint[EP_NUMBER].dpram_address;
}

void *get_pico_endpoint_dpram_address(uint8_t EP_NUMBER) {
    
    return pico_endpoint[EP_NUMBER].dpram_address;
}

void set_host_callback_handler(uint8_t EP_NUMBER, void *callback_handler) {
    
    host_endpoint[EP_NUMBER].callback_handler = callback_handler;
}

void *get_pico_endpoint_handler(uint8_t EP_NUMBER) {
    
    return pico_endpoint[EP_NUMBER].endpoint_handler;
}

void set_pico_endpoint_handler(uint8_t EP_NUMBER, void *endpoint_handler) {
    
    pico_endpoint[EP_NUMBER].endpoint_handler = endpoint_handler;
}

void *get_pico_callback_handler(uint8_t EP_NUMBER) {
    
    return pico_endpoint[EP_NUMBER].callback_handler;
}

void set_pico_callback_handler(uint8_t EP_NUMBER, void *callback_handler) {
    
    pico_endpoint[EP_NUMBER].callback_handler = callback_handler;
}

void set_endpoint_busy_to_host(uint8_t EP_NUMBER, bool ep_busy) {
    
    host_endpoint[EP_NUMBER].ep_busy = ep_busy;
}

void set_endpoint_busy_to_pico(uint8_t EP_NUMBER, bool ep_busy) {
    
    pico_endpoint[EP_NUMBER].ep_busy = ep_busy;
}

bool get_endpoint_busy_to_host(uint8_t EP_NUMBER) {
    
    return host_endpoint[EP_NUMBER].ep_busy;
}

bool get_endpoint_busy_to_pico(uint8_t EP_NUMBER) {
    
    return pico_endpoint[EP_NUMBER].ep_busy;
}

bool get_endpoint_idle_to_host(uint8_t EP_NUMBER) {
	
	return !host_endpoint[EP_NUMBER].ep_busy;
}

bool get_endpoint_idle_to_pico(uint8_t EP_NUMBER) {
    
    return !pico_endpoint[EP_NUMBER].ep_busy;
}

uint16_t get_host_endpoint_max_packet_size(uint8_t EP_NUMBER) {
    
    return host_endpoint[EP_NUMBER].max_packet_size;
}

uint16_t get_pico_endpoint_max_packet_size(uint8_t EP_NUMBER) {
    
    return pico_endpoint[EP_NUMBER].max_packet_size;
}

uint8_t get_host_endpoint_transfer_type(uint8_t EP_NUMBER) {
    
    return host_endpoint[EP_NUMBER].transfer_type;
}

uint8_t get_pico_endpoint_transfer_type(uint8_t EP_NUMBER) {
    
    return pico_endpoint[EP_NUMBER].transfer_type;
}