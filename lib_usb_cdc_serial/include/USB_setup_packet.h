/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define USB_REQ_TYPE_STANDARD       0x00
#define USB_REQ_TYPE_TYPE_MASK      0x60
#define USB_REQ_TYPE_TYPE_CLASS     0x20
#define USB_REQ_TYPE_TYPE_VENDOR    0x40

#define PICO_TO_HOST_DIRECTION_MASK         0x80
#define USB_REQ_TYPE_RECIPIENT_MASK         0x1f
#define USB_REQ_TYPE_RECIPIENT_DEVICE       0x00
#define USB_REQ_TYPE_RECIPIENT_INTERFACE    0x01
#define USB_REQ_TYPE_RECIPIENT_ENDPOINT     0x02

struct usb_setup_command {

    uint8_t descriptor_type;
    uint8_t descriptor_index;
    uint8_t request_type;
    uint8_t direction;
    uint8_t recipient;
    uint8_t request;
    uint16_t length;
    uint16_t value;
    uint16_t index;
 
} __packed;

typedef struct usb_setup_command usb_setup_t;

extern usb_setup_t *setup;
extern volatile uint8_t *setup_packet;

void usb_setup_interface();
void usb_handle_setup_packet();

static inline void prepare_setup_packet();
static inline void prepare_control_endpoints();
static inline void prepare_control_setup_direction();

static inline void usb_setup_type_unknown();