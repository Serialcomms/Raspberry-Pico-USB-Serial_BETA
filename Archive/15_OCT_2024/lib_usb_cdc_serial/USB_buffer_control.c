/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/regs/usb.h"      
#include "hardware/structs/usb.h"
#include "include/USB_buffer_control.h"
#include "include/USB_endpoint_struct.h"

uint32_t get_last_data_pid_to_pico(uint8_t EP_NUMBER) {

  return (usb_dpram->ep_buf_ctrl[EP_NUMBER].out & USB_BUF_CTRL_DATA1_PID) ? USB_BUF_CTRL_DATA1_PID : USB_BUF_CTRL_DATA0_PID;

}

uint32_t get_last_data_pid_to_host(uint8_t EP_NUMBER) {

  return (usb_dpram->ep_buf_ctrl[EP_NUMBER].in & USB_BUF_CTRL_DATA1_PID) ? USB_BUF_CTRL_DATA1_PID : USB_BUF_CTRL_DATA0_PID;

}

uint32_t get_next_data_pid_to_pico(uint8_t EP_NUMBER) {

  return pico_endpoint[EP_NUMBER].next_packet_id;

}

uint32_t get_next_data_pid_to_host(uint8_t EP_NUMBER) {

  return host_endpoint[EP_NUMBER].next_packet_id;

}

void set_next_data_pid_to_pico(uint8_t EP_NUMBER, uint32_t data_pid) {

  pico_endpoint[EP_NUMBER].next_packet_id = data_pid ? USB_BUF_CTRL_DATA1_PID : USB_BUF_CTRL_DATA0_PID;

}

void set_next_data_pid_to_host(uint8_t EP_NUMBER, uint32_t data_pid) {

  host_endpoint[EP_NUMBER].next_packet_id = data_pid ? USB_BUF_CTRL_DATA1_PID : USB_BUF_CTRL_DATA0_PID;

}

void toggle_next_data_pid_to_pico(uint8_t EP_NUMBER) {
  
  pico_endpoint[EP_NUMBER].next_packet_id = pico_endpoint[EP_NUMBER].next_packet_id ? USB_BUF_CTRL_DATA0_PID : USB_BUF_CTRL_DATA1_PID;

}

void toggle_next_data_pid_to_host(uint8_t EP_NUMBER) {
  
  host_endpoint[EP_NUMBER].next_packet_id = host_endpoint[EP_NUMBER].next_packet_id ? USB_BUF_CTRL_DATA0_PID : USB_BUF_CTRL_DATA1_PID;

}

void set_buffer_control_dispatch_to_host(uint8_t EP_NUMBER, uint32_t buffer_dispatch) {

  usb_dpram->ep_buf_ctrl[EP_NUMBER].in &= USB_BUF_CTRL_LEN_MASK;
  
  usb_dpram->ep_buf_ctrl[EP_NUMBER].in |= buffer_dispatch;

}

void set_buffer_control_dispatch_to_pico(uint8_t EP_NUMBER, uint32_t buffer_dispatch) {

  usb_dpram->ep_buf_ctrl[EP_NUMBER].out &= USB_BUF_CTRL_LEN_MASK;

  usb_dpram->ep_buf_ctrl[EP_NUMBER].out |= buffer_dispatch;

}

void set_buffer_control_available_to_host(uint8_t EP_NUMBER, bool AVAILABLE) {

  if (AVAILABLE) {

    usb_dpram->ep_buf_ctrl[EP_NUMBER].in |= USB_BUF_CTRL_AVAIL;

  } else {

    usb_dpram->ep_buf_ctrl[EP_NUMBER].in &= ~USB_BUF_CTRL_AVAIL;

  }
}

void set_buffer_control_available_to_pico(uint8_t EP_NUMBER, bool AVAILABLE) {

  if (AVAILABLE) {

    usb_dpram->ep_buf_ctrl[EP_NUMBER].out |= USB_BUF_CTRL_AVAIL;

  } else {

    usb_dpram->ep_buf_ctrl[EP_NUMBER].out &= ~USB_BUF_CTRL_AVAIL;

  }
}

void set_buffer_control_transfer_bytes_to_pico(uint8_t EP_NUMBER, uint16_t transfer_bytes) {

  usb_dpram->ep_buf_ctrl[EP_NUMBER].out &= ~USB_BUF_CTRL_LEN_MASK;
  usb_dpram->ep_buf_ctrl[EP_NUMBER].out |= transfer_bytes;

}

void set_buffer_control_transfer_bytes_to_host(uint8_t EP_NUMBER, uint16_t transfer_bytes) {

  usb_dpram->ep_buf_ctrl[EP_NUMBER].in &= ~USB_BUF_CTRL_LEN_MASK;
  usb_dpram->ep_buf_ctrl[EP_NUMBER].in |= transfer_bytes;

}

uint32_t get_buffer_control_transfer_bytes_to_pico(uint8_t EP_NUMBER) {

  return usb_dpram->ep_buf_ctrl[EP_NUMBER].out & USB_BUF_CTRL_LEN_MASK;

}

uint32_t get_buffer_control_transfer_bytes_to_host(uint8_t EP_NUMBER) {

  return usb_dpram->ep_buf_ctrl[EP_NUMBER].in & USB_BUF_CTRL_LEN_MASK;

}
