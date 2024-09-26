/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/regs/usb.h"             
#include "hardware/structs/usb.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_address.h"

void set_pico_device_address(uint16_t DEVICE_ADDRESS) {

  send_zlp_to_host(0);
  
  busy_wait_ms(1);

  usb_hardware_set->dev_addr_ctrl = DEVICE_ADDRESS & DEVICE_ADDRESS_MASK;
 
}

uint8_t get_pico_device_address() {

  return usb_hw->dev_addr_ctrl & DEVICE_ADDRESS_MASK;

}