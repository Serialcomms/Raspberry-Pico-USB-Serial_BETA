/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define buffer_direction_to_host 0
#define buffer_direction_to_pico 1

static inline void build_queue_transfer_to_host(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);
static inline void prepare_queue_transfer_to_host(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);
static inline void queue_try_extend_transfer_to_host(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);
static inline uint16_t build_first_packet_to_host(uint8_t EP_NUMBER);

void start_queue_transfer_to_host(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);