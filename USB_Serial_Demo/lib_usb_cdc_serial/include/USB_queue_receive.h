
/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define buffer_direction_to_host 0
#define buffer_direction_to_pico 1

static inline bool wait_for_new_data_from_host(uint8_t EP_NUMBER, uint16_t wait_milliseconds);
void start_queue_receive_to_pico(uint8_t EP_NUMBER, uint16_t wait_milliseconds);
int16_t start_queue_transfer_to_pico(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes);
int16_t copy_queue_bytes_to_pico_buffer(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes);