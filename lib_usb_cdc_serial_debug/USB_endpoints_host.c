
/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/regs/usb.h"
#include "hardware/structs/usb.h"
#include "include/USB_uart_printf.h"
#include "include/USB_descriptor_device.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoints_host.h"

struct endpoint_profile host_endpoint[15];

void usb_build_host_endpoint(uint8_t EP_NUMBER, uint16_t TRANSFER_TYPE, uint16_t QUEUE_SIZE, void *endpoint_handler) {

  if (EP_NUMBER > 0) {

    build_host_function_endpoint(EP_NUMBER, TRANSFER_TYPE, QUEUE_SIZE, endpoint_handler);

  } else {

    build_host_default_endpoint(QUEUE_SIZE, endpoint_handler);

  }

}

static inline void build_host_function_endpoint(uint8_t EP_NUMBER, uint16_t TRANSFER_TYPE, uint16_t QUEUE_SIZE, void *endpoint_handler) {

  uint8_t EP_OFFSET = EP_NUMBER - 1;

  void *usb_dpram_address = &usb_dpram->epx_data[(64 * 2 * EP_OFFSET) + 0x0000];  // first half of available dpram

  host_endpoint[EP_NUMBER].ep_busy = false;
  host_endpoint[EP_NUMBER].queue_busy = false;
  host_endpoint[EP_NUMBER].queue_long = false;
  host_endpoint[EP_NUMBER].max_packet_size = 64;
  host_endpoint[EP_NUMBER].transfer_type = TRANSFER_TYPE;
  host_endpoint[EP_NUMBER].dpram_address = usb_dpram_address;
  host_endpoint[EP_NUMBER].endpoint_handler = endpoint_handler;
  host_endpoint[EP_NUMBER].callback_handler = NULL;

  uint32_t address_base_offset = usb_buffer_offset(host_endpoint[EP_NUMBER].dpram_address); 
  uint32_t ep_control_register = endpoint_control_base_config(TRANSFER_TYPE, address_base_offset);

  usb_dpram->ep_ctrl[EP_OFFSET].in = ep_control_register;

  if (QUEUE_SIZE) queue_init(&host_endpoint[EP_NUMBER].data_queue, sizeof(uint8_t), QUEUE_SIZE);
  
  uart_printf("Build Host Function Endpoint %d, Queue Size=%d, Endpoint Control=%08X\n\r", EP_NUMBER, QUEUE_SIZE, ep_control_register);

}

static inline void build_host_default_endpoint(uint16_t QUEUE_SIZE, void *endpoint_handler) {

  void *usb_dpram_address = &usb_dpram->ep0_buf_a[0];   // address fixed in Pico. in/out shared

  host_endpoint[0].ep_busy = false; 
  host_endpoint[0].queue_busy = false;
  host_endpoint[0].queue_long = false;
  host_endpoint[0].max_packet_size = ep0_packet_size();
  host_endpoint[0].transfer_type = USB_TRANSFER_TYPE_CONTROL;
  host_endpoint[0].dpram_address = usb_dpram_address;
  host_endpoint[0].endpoint_handler = endpoint_handler;
  host_endpoint[0].callback_handler = NULL;
  
  // there is no endpoint control register for EP0, interrupt enable for EP0 comes from SIE_CTRL

  usb_hw->sie_ctrl |= USB_SIE_CTRL_EP0_INT_1BUF_BITS;

  if (QUEUE_SIZE) queue_init(&host_endpoint[0].data_queue, sizeof(uint8_t), QUEUE_SIZE);

  uart_printf("Build Host Default Endpoint %d, DPRAM Address=%08X\n\r", 0, usb_dpram_address);
 
}

static inline uint32_t usb_buffer_offset(volatile uint8_t *buffer) {  // from pico-examples

  return (uint32_t) buffer ^ (uint32_t) usb_dpram;

}

static inline uint32_t endpoint_control_base_config(uint8_t TRANSFER_TYPE, uint32_t address_base) {

  uint32_t base_config = address_base;

  base_config |= EP_CTRL_ENABLE_BITS;
  base_config |= EP_CTRL_INTERRUPT_PER_BUFFER;
  base_config |= TRANSFER_TYPE << EP_CTRL_BUFFER_TYPE_LSB;

  return base_config;

}