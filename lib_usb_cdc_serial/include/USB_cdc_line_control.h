/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define ON  true
#define OFF false

#define BITMAP_DTR  0x0001
#define BITMAP_RTS  0x0002

#define BITMAP_DCD  0x0001
#define BITMAP_DSR  0x0002
#define BITMAP_RING 0x0008

#define USB_CDC_NOTIFY_CLASS_REQUEST  0xA1
#define USB_CDC_NOTIFY_SERIAL_STATE   0x20
#define USB_CDC_NOTIFY_RING_STATE     0x09

typedef struct __packed usb_request {

  uint8_t   RequestType;
  uint8_t   Request;
  uint16_t  Value;
  uint16_t  Index;
  uint16_t  Length;

} usb_request_t;

typedef struct __packed serial_state {   // 10 bytes

  usb_request_t request;
  uint16_t      data;
  
} cdc_notify_serial_state_t;

extern cdc_notify_serial_state_t cdc_notify_serial_state;

void cdc_class_set_line_control();

void cdc_class_send_line_notification();

void cdc_class_set_default_line_state();

void cdc_class_set_notify_line_state(bool send_line_state);