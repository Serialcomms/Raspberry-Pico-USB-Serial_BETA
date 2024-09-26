/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/structs/usb.h" 
#include "include/USB_queue_transmit.h"
#include "include/USB_buffer_control.h"
#include "include/USB_queue_control.h"
#include "include/USB_EP1_handlers.h"

void ep1_handler_to_host () {

    clear_buffer_status(USB_BUFF_STATUS_EP1_IN_BITS); 

    toggle_next_data_pid_to_host(1);

    set_queue_busy_to_host(1, false);

}

static inline void clear_buffer_status (uint32_t buffer_mask) {

    usb_hardware_clear->buf_status = buffer_mask;
  
}