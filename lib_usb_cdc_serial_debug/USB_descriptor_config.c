/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_descriptor_config.h"

#define CDC_REVISION_BCD    0x0120  // CDC Class Revision 1.20
#define ACM_CAPABILITIES    0x02    // ACM Capabilities (Bit D1) = Device supports set/get line coding, set/notify state 
#define CALL_CAPABILITIES   0x01    // CCI Capabilities (Bit D0) = Device handles call management itself 

const uint8_t pico_config_descriptor[] = {

  0x09, 0x02, 0x4B, 0x00, 0x02, 0x01, 0x00, 0x80, 0xFA,           // Configuration Descriptor
  0x08, 0x0B, 0x00, 0x02, 0x02, 0x02, 0x00, 0x00,                 // Interface Association Descriptor (IAD)
  0x09, 0x04, 0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x00,           // CDC Class Interface Descriptor (CCI)
  
  // CDC Class Specific (CS) Functional Descriptors - USB_CDC_v1.2 table 18 
  0x05, 0x24, 0x00, USB_CDC_REVISION,                             // CDC Functional Descriptor - Header 
  0x04, 0x24, 0x02, ACM_CAPABILITIES,                             // CDC Functional Descriptor - Abstract Control Management 
  0x05, 0x24, 0x06, 0x00, 0x01,                                   // CDC Functional Descriptor - Union 
  0x05, 0x24, 0x01, CALL_CAPABILITIES, 0x00,                      // CDC Functional Descriptor - Call Management  
  0x07, 0x05, 0x81, 0x03, 0x10, 0x00, 0x01,                       // Endpoint Descriptor: EP1 In - (max packet size = 16)
  
  0x09, 0x04, 0x01, 0x00, 0x02, 0x0A, 0x00, 0x00, 0x00,           // CDC Data Class Interface Descriptor: CDC Data 
  0x07, 0x05, 0x82, 0x02, 0x40, 0x00, 0x00,                       // Endpoint Descriptor: EP2 In  - Bulk Transfer Type
  0x07, 0x05, 0x02, 0x02, 0x40, 0x00, 0x00                        // Endpoint Descriptor: EP2 Out - Bulk Transfer Type

};

const uint16_t config_total_length() {

  return pico_config_descriptor[3] << 8 | pico_config_descriptor[2];

}