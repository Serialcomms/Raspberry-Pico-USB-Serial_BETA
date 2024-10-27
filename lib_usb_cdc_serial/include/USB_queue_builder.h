/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

bool __not_in_flash_func(add_source_data_to_host_queue)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);
bool __not_in_flash_func(add_source_data_to_pico_queue)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length);