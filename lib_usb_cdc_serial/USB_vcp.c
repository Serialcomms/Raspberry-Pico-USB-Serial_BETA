/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <pico/stdio.h>
#include <pico/stdio/driver.h>
#include "pico/stdlib.h"
#include "pico/error.h"

#include "include/USB_vcp.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_data_packet.h"
#include "include/USB_queue_transmit.h"
#include "include/USB_queue_receive.h"

stdio_driver_t virtual_com_port;

void (*chars_available_callback)(void*);
void *chars_available_param;

void init_usb_vcp_serial(bool set_cr_lf, bool set_exclusive) {

    CDC_CONFIGURATION_SET = false;  

    init_virtual_com_port();

    stdio_set_driver_enabled(&virtual_com_port, true);
	
    if (set_cr_lf) virtual_com_port.crlf_enabled = true;

    if (set_exclusive) stdio_filter_driver(&virtual_com_port);

}

void deinit_usb_vcp_serial() {
    
    CDC_CONFIGURATION_SET = false;
    
    chars_available_callback = NULL;
    
    chars_available_param = NULL;

    stdio_set_driver_enabled(&virtual_com_port, false);

}

void vcp_out_func(const char *host_buffer, int host_buffer_length) {

    start_queue_transfer_to_host(2, host_buffer, host_buffer_length);
}

int vcp_in_func(char *pico_buffer, int pico_buffer_bytes) {

    return start_queue_transfer_to_pico(2, pico_buffer, pico_buffer_bytes);

}    

void vcp_out_flush() {

  
}

void vcp_set_chars_available_callback(void (*fn)(void*), void *param) {

    chars_available_callback = fn;
    chars_available_param = param;
}

void init_virtual_com_port() {

    virtual_com_port.in_chars = vcp_in_func;
    virtual_com_port.out_chars = vcp_out_func;
    virtual_com_port.out_flush = vcp_out_flush;

    virtual_com_port.crlf_enabled = false;
    virtual_com_port.last_ended_with_cr = false;
    virtual_com_port.next = (stdio_driver_t *) 0;
    virtual_com_port.set_chars_available_callback = vcp_set_chars_available_callback;

}