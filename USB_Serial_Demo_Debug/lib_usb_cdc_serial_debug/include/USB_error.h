/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

enum USB_ERROR_LEVELS {

    USB_ERROR_LEVEL_NONE = 0,
    USB_ERROR_LEVEL_INFO = 1,
    USB_ERROR_LEVEL_WARN = 2,
    USB_ERROR_LEVEL_BOOT = 9,
    
    USB_ERROR_LEVEL_ERROR = 3,
    USB_ERROR_LEVEL_QUEUE = 100,
    USB_ERROR_LEVEL_FATAL = 999,

};

void usb_error(uint8_t error_level);