/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "include/USB_setup_control.h"
#include "include/USB_setup_packet.h"
#include "include/USB_data_packet.h"
#include "include/USB_queue_transmit.h"

#include "include/USB_com_port_signalling.h"
#include "include/USB_EP0_handlers.h"
#include "include/USB_buffer_control.h"
#include "include/USB_cdc_line_control.h"
#include "include/USB_uart_printf.h"

cdc_notify_serial_state_t cdc_notify_serial_state;

void cdc_class_set_line_control() {

  uint8_t cdc_interface = setup->index;

  pico_com_port.signalling.DTE.DTR = (setup->value & BITMAP_DTR) ? ON : OFF;
  pico_com_port.signalling.DTE.RTS = (setup->value & BITMAP_RTS) ? ON : OFF;

  show_set_line_control(setup->index, setup->value);

  send_zlp_to_host(0);

}

void cdc_class_send_line_notification() {

  void *line_notification = &cdc_notify_serial_state;
  
  uint8_t line_notification_size = sizeof(cdc_notify_serial_state);

  show_send_line_notification();
  
  start_queue_transfer_to_host(3, line_notification, line_notification_size);

  show_set_notify_line_state(line_notification, line_notification_size);

}

void cdc_class_set_default_line_state() {

  pico_com_port.signalling.DCE.DSR  = OFF;
  pico_com_port.signalling.DCE.CTS  = OFF;
  pico_com_port.signalling.DCE.DCD  = OFF;
  pico_com_port.signalling.DCE.RING = OFF;
    
  pico_com_port.signalling.DTE.DTR  = OFF;
  pico_com_port.signalling.DTE.RTS  = OFF;

}

void cdc_class_set_notify_line_state(bool send_line_state) {

  cdc_notify_serial_state.request.RequestType = USB_CDC_NOTIFY_CLASS_REQUEST;
  cdc_notify_serial_state.request.Request = USB_CDC_NOTIFY_SERIAL_STATE;
  cdc_notify_serial_state.request.Value = 0x0000;
  cdc_notify_serial_state.request.Index = 0x0000;
  cdc_notify_serial_state.request.Length = sizeof(uint16_t);
    
  cdc_notify_serial_state.data = 0;

  if (pico_com_port.signalling.DCE.DCD)   cdc_notify_serial_state.data |= BITMAP_DCD;
  if (pico_com_port.signalling.DCE.DSR)   cdc_notify_serial_state.data |= BITMAP_DSR;
  if (pico_com_port.signalling.DCE.RING)  cdc_notify_serial_state.data |= BITMAP_RING;

  uart_printf("COM Port Set Notify Line State = %04X\n\r", cdc_notify_serial_state.data);

  if (send_line_state) cdc_class_send_line_notification();

}

void show_set_notify_line_state(void *line_notification, uint8_t line_notification_size) {

uint8_t *line_notification_data = line_notification;

  uart_printf("Sending Set Notify Line State=%04X, Size=%d, Bytes=%02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X\n\r", 
  cdc_notify_serial_state.data, 
  line_notification_size,
  line_notification_data[0],
  line_notification_data[1],
  line_notification_data[2],
  line_notification_data[3],
  line_notification_data[4],
  line_notification_data[5],
  line_notification_data[6],
  line_notification_data[7],
  line_notification_data[8],
  line_notification_data[9]);

}