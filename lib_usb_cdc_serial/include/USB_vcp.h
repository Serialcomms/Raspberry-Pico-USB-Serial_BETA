/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

extern bool CDC_CONFIGURATION_SET;

void init_usb_vcp_serial(bool set_cr_lf, bool set_exclusive);

void deinit_usb_vcp_serial();

void init_virtual_com_port();

void vcp_out_flush(void);

int vcp_in_func(char *pico_buffer, int pico_buffer_bytes);

void vcp_out_func(const char *host_buffer, int host_buffer_length);

void vcp_set_chars_available_callback(void (*fn)(void*), void *param);

extern void (*chars_available_callback)(void*);
extern void *chars_available_param;

extern stdio_driver_t virtual_com_port;