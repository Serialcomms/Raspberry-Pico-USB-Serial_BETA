/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_descriptor_device.h"

//https://github.com/raspberrypi/usb-pid

#define VENDOR_ID         0x2E8A  // Raspberry Pi
#define PRODUCT_ID        0x000A  // Raspberry Pi Pico SDK CDC UART (RP2040)
#define PRODUCT_BCD       0x0101  // Product version 1.01
#define VERSION_BCD       0x0110  // USB Version 1.10
#define USB_EP0_MAX       0x40    // 64 bytes

const uint8_t pico_device_descriptor[] = {

  USB_DEVICE_DESCRIPTOR,  
  USB_VERSION_BCD,
  USB_MISC_IAD_DEVICE,
  USB_EP0_MAX,                    // EP0 MAX PACKET SIZE
  USB_VENDOR_ID,
  USB_PRODUCT_ID,
  USB_PRODUCT_BCD,
  0x01,                           // STRING_MANUFACTURER 
  0x02,                           // STRING_PRODUCT 
  0x00,                           // STRING_SERIAL 
  0x01                            // CONFIGURATIONS

};

const uint16_t usb_vendor_id() {

  return pico_device_descriptor[9] << 8 | pico_device_descriptor[8];

}

const uint16_t usb_product_id() {

  return pico_device_descriptor[11] << 8 | pico_device_descriptor[10];

}

const float usb_device_version() {

  return bcd_convert(pico_device_descriptor[3] , pico_device_descriptor[2]);

}

const float usb_device_release() {

  return bcd_convert(pico_device_descriptor[13] , pico_device_descriptor[12]);

}

const uint8_t ep0_packet_size() {

    if (pico_device_descriptor[7]==16 | 
        pico_device_descriptor[7]==32 | 
        pico_device_descriptor[7]==64 ) 

    {
      return pico_device_descriptor[7];
    
    } else {

      return DEVICE_DESCRIPTOR_DEFAULT_SIZE;
    
    }
}

float bcd_convert(uint8_t major, uint8_t minor) {

  const float TEN = 10;
 
  uint8_t major_tens = MIN(major >> 4, 9);
  uint8_t minor_tens = MIN(minor >> 4, 9);
  
  uint8_t major_units = MIN(major & 0xF, 9);
  uint8_t minor_units = MIN(minor & 0xF, 9);

  float integer_part    = major_tens * TEN + major_units;
  float fractional_part = minor_tens * TEN + minor_units;

  return integer_part + fractional_part / (TEN * TEN);

}