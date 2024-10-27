/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

extern bool CDC_CONFIGURATION_SET;

void usb_start_serial(bool set_cr_lf, bool set_exclusive, bool set_suspend_resume);
void usb_stop_serial();

void set_com_port_dcd(bool dcd_state);
void set_com_port_dsr(bool dsr_state);
void set_com_port_ring(bool ring_state);

bool get_com_port_dtr();
bool get_com_port_rts(); 

bool get_cdc_configuration_set();

void wakeup_remote_usb_host();