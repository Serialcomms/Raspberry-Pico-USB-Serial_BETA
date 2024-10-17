/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define buffer_direction_to_host 0
#define buffer_direction_to_pico 1

void  __not_in_flash_func(start_queue_transfer_to_host)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);

static inline void  __not_in_flash_func(start_bulk_transfer)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);

static inline void start_control_transfer(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);
static inline void start_interrupt_transfer(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);

static inline void  __not_in_flash_func(start_bulk_transfer_single)(uint8_t EP_NUMBER, const uint8_t *source_data);
static inline void  __not_in_flash_func(start_bulk_transfer_multi)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length); 

static inline void  __not_in_flash_func(send_queue_data_packet_to_host)(uint8_t EP_NUMBER); 

static inline void  __not_in_flash_func(copy_source_data_to_host_queue)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);
static inline void  __not_in_flash_func(copy_source_data_to_host_buffer)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);