/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define USB_TRANSFER_TYPE_CONTROL       0x0
#define USB_TRANSFER_TYPE_ISOCHRONOUS   0x1
#define USB_TRANSFER_TYPE_BULK          0x2
#define USB_TRANSFER_TYPE_INTERRUPT     0x3
#define USB_TRANSFER_TYPE_BITS          0x3

void usb_build_default_endpoints();
void usb_build_function_endpoints();