/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "include/USB_com_port_framing.h"

const uint8_t vcp_valid_stop_bits[]     = {0, 1, 2};           // 1, 1.5, 2
const uint8_t vcp_valid_data_bits[]     = {5, 6, 7, 8};
const uint8_t vcp_valid_parity_bit[]    = {0, 1, 2 ,3, 4};     // N-O-E-M-S
const uint32_t vcp_valid_baud_rates[]   = {1200, 9600, 19200, 57600, 115200};

bool valid_framing(uint32_t baud, uint32_t parity, uint32_t stop) {

  return (valid_baud_rate(baud) & valid_parity_bits(parity) & valid_stop_bits(stop));

}

bool valid_baud_rate(uint32_t validate_baud) {

  uint8_t baud_rates = count_of(vcp_valid_baud_rates);

  uint8_t index = 0;

  do {

    if (validate_baud == vcp_valid_baud_rates[index]) return true;

  } while (++index < baud_rates);
    
  return false;

}

bool valid_stop_bits(uint32_t validate_stop) {

  uint8_t stop_bit_count = count_of(vcp_valid_stop_bits);

  uint8_t index = 0;

  do {

    if (validate_stop == vcp_valid_stop_bits[index]) return true;

  } while (++index < stop_bit_count);
    
  return false;

}

bool valid_parity_bits(uint32_t validate_parity) {

  uint8_t parity_bit_count = count_of(vcp_valid_parity_bit);

  uint8_t index = 0;

  do {

    if (validate_parity == vcp_valid_parity_bit[index]) return true;

  } while (++index < parity_bit_count);
    
  return false;

}