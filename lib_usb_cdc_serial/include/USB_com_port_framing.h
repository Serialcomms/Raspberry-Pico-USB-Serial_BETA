/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

bool valid_baud_rate(uint32_t validate_baud);
bool valid_stop_bits(uint32_t validate_stop);
bool valid_parity_bits(uint32_t validate_parity);
bool valid_framing(uint32_t validate_baud, uint32_t validate_parity, uint32_t validate_stop);