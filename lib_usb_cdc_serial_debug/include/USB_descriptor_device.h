/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define MASK 0xFF 

#define DEVICE_DESCRIPTOR_DEFAULT_SIZE 8

#define USB_DEVICE_DESCRIPTOR 0x12, 0x01
#define USB_MISC_IAD_DEVICE 0xEF, 0x02, 0x01

#define USB_VID(VENDOR_ID)(VENDOR_ID & MASK), (VENDOR_ID >> 8 & MASK)
#define USB_VENDOR_ID USB_VID(VENDOR_ID)

#define USB_PID(PRODUCT_ID)(PRODUCT_ID & MASK), (PRODUCT_ID >> 8 & MASK)
#define USB_PRODUCT_ID USB_PID(PRODUCT_ID)

#define USB_P_BCD(PRODUCT_BCD)(PRODUCT_BCD & MASK), (PRODUCT_BCD >> 8 & MASK)
#define USB_PRODUCT_BCD USB_P_BCD(PRODUCT_BCD)

#define USB_V_BCD(VERSION_BCD)(VERSION_BCD & MASK), (VERSION_BCD >> 8 & MASK)
#define USB_VERSION_BCD USB_V_BCD(VERSION_BCD)

extern const uint8_t pico_device_descriptor[];

const uint8_t ep0_packet_size();
const uint16_t usb_vendor_id();
const uint16_t usb_product_id();

const uint16_t config_total_length();

const float usb_device_version();
const float usb_device_release();

float bcd_convert(uint8_t major, uint8_t minor);