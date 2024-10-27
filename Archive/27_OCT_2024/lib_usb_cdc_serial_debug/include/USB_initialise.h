/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define USB_REGISTER_VALUE  USB_MAIN_CTRL_CONTROLLER_EN_BITS
#define MUX_REGISTER_VALUE  USB_USB_MUXING_TO_PHY_BITS
#define IRQ_REGISTER_VALUE  USB_INTS_BUS_RESET_BITS
#define PWR_REGISTER_VALUE  USB_USB_PWR_VBUS_DETECT_BITS | USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_BITS
#define SIE_REGISTER_VALUE  0

void usb_device_init();
void usb_insert_device();
void usb_remove_device();

static inline void clear_usb_dpsram();
static inline void set_usb_hw_registers();