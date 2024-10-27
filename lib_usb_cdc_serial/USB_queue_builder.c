/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_error.h"
#include "include/USB_queue_control.h"
#include "include/USB_queue_builder.h"

bool __not_in_flash_func(add_source_data_to_host_queue)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {
    
    bool queue_add_result = false;
    uint16_t source_data_offset = 0;

    do {

        queue_add_result = queue_try_add_to_host(EP_NUMBER, &source_data[source_data_offset]);

    } while (queue_add_result && ++source_data_offset < source_data_length);

    return queue_add_result;
    
}

bool __not_in_flash_func(add_source_data_to_pico_queue)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {
    
    bool queue_add_result = false;
    uint16_t source_data_offset = 0;

    do {

        queue_add_result = queue_try_add_to_pico(EP_NUMBER, &source_data[source_data_offset]);

    } while (queue_add_result && ++source_data_offset < source_data_length);

    return queue_add_result;
    
}