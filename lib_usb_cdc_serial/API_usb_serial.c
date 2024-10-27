/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "API_usb_serial.h"
#include "include/USB_vcp.h"
#include "include/USB_initialise.h"
#include "include/USB_suspend_resume.h"
#include "include/USB_com_port_signalling.h"

void usb_start_serial(bool set_cr_lf, bool set_exclusive, bool set_suspend_resume) {
	
    usb_device_init();

    usb_insert_device();

    busy_wait_ms(333);

    init_usb_vcp_serial(set_cr_lf, set_exclusive);
	
	usb_device_set_suspend_resume_mode(set_suspend_resume);

}

void usb_stop_serial() {
  
  stdio_set_chars_available_callback(NULL, NULL);
  
  stdio_set_driver_enabled(&virtual_com_port, false);

  usb_remove_device();

}

void set_com_port_dcd(bool dcd_state) {

  com_port_set_dcd(dcd_state);   

}

void set_com_port_dsr(bool dsr_state) {

  com_port_set_dsr(dsr_state);   

}

void set_com_port_ring(bool ring_state) {

  com_port_set_ring(ring_state);   

}

bool get_com_port_dtr() {

  return com_port_get_dtr();

}

bool get_com_port_rts() {

  return com_port_get_rts();

}

bool get_cdc_configuration_set() {

  return CDC_CONFIGURATION_SET;

}

void wakeup_remote_usb_host() {

  usb_device_wake_remote_host();

}