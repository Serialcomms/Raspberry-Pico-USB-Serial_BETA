/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/structs/usb.h"           // USB hardware struct definitions
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoint_control.h"
#include "include/USB_queue_transmit.h"
#include "include/USB_buffer_control.h"
#include "include/USB_queue_control.h"
#include "include/USB_EP3_handlers.h"

irq_handler_t ep3_handler_to_host() {

    clear_buffer_status(USB_BUFF_STATUS_EP3_IN_BITS); 

    toggle_next_data_pid_to_host(3);

    set_endpoint_busy_to_host(3, false);
 
}

static inline void clear_buffer_status (uint32_t buffer_mask) {

    usb_hardware_clear->buf_status = buffer_mask;
  
}