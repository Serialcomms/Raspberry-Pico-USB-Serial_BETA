/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define CDC_CLASS_SET_LINE_CODING   0x20
#define CDC_CLASS_GET_LINE_CODING   0x21
#define CDC_CLASS_SET_LINE_CONTROL  0x22
#define CDC_CLASS_SET_LINE_BREAK    0x23

void usb_setup_class_cdc();
static inline void usb_setup_class_cdc_unknown();