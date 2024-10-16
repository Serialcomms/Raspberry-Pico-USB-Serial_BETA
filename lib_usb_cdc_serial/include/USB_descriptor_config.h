/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define CDC_MASK 0xFF
#define CDC_REVISION(CDC_REVISION_BCD)(CDC_REVISION_BCD & CDC_MASK), (CDC_REVISION_BCD >> 8 & CDC_MASK)
#define USB_CDC_REVISION CDC_REVISION(CDC_REVISION_BCD)

extern const uint8_t pico_config_descriptor[];

const uint16_t config_total_length();