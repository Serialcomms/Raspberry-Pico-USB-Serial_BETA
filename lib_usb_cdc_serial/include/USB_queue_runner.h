/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

void __not_in_flash_func(start_queue_runner_to_host)(uint8_t EP_NUMBER);

int16_t __not_in_flash_func(dequeue_bytes_to_pico_buffer)(uint8_t EP_NUMBER, void *pico_buffer, uint16_t pico_buffer_bytes);
int16_t __not_in_flash_func(dequeue_bytes_to_host_buffer)(uint8_t EP_NUMBER, void *host_buffer, uint16_t host_buffer_bytes);