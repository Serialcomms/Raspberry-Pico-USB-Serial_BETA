/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

void *get_host_endpoint_handler(uint8_t EP_NUMBER);
void *get_host_callback_handler(uint8_t EP_NUMBER);

void set_host_endpoint_handler(uint8_t EP_NUMBER, void *endpoint_handler);
void set_host_callback_handler(uint8_t EP_NUMBER, void *callback_handler);

void usb_build_host_endpoint(uint8_t EP_NUMBER, uint16_t TRANSFER_TYPE, uint16_t QUEUE_SIZE, void *endpoint_handler);

static inline uint32_t usb_buffer_offset(volatile uint8_t *buffer);
static inline uint32_t endpoint_control_base_config(uint8_t TRANSFER_TYPE, uint32_t address_base);

static inline void build_host_default_endpoint(uint16_t QUEUE_SIZE, void *endpoint_handler);
static inline void build_host_function_endpoint(uint8_t EP_NUMBER, uint16_t TRANSFER_TYPE, uint16_t QUEUE_SIZE, void *endpoint_handler);