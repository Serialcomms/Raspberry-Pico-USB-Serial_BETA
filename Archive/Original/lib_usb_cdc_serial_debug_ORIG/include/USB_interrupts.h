/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define usb_hardware_set   ((usb_hw_t *)hw_set_alias_untyped(usb_hw))
#define usb_hardware_clear ((usb_hw_t *)hw_clear_alias_untyped(usb_hw))

#define SEPARATOR "-----------------------------------------------------------------------------------------\n\r"

#define USB_INTS_SIE_RECEIVE_ERRORS (USB_INTS_ERROR_RX_TIMEOUT_BITS | USB_INTS_ERROR_RX_OVERFLOW_BITS | USB_INTS_ERROR_BIT_STUFF_BITS | USB_INTS_ERROR_CRC_BITS)
#define USB_INTS_HOST_EVENTS        (USB_INTS_DEV_RESUME_FROM_HOST_BITS | USB_INTS_HOST_SOF_BITS | USB_INTS_HOST_RESUME_BITS | USB_INTS_HOST_CONN_DIS_BITS)
#define USB_INTS_DEVICE_EVENTS      (USB_INTS_DEV_SOF_BITS | USB_INTS_DEV_SUSPEND_BITS | USB_INTS_DEV_CONN_DIS_BITS)
#define USB_INTS_ENDPOINT_EVENTS    (USB_INTS_EP_STALL_NAK_BITS | USB_INTS_ABORT_DONE_BITS | USB_INTS_STALL_BITS | USB_INTS_TRANS_COMPLETE_BITS)
#define USB_INTS_ALL_OTHER_EVENTS   (USB_INTS_HOST_EVENTS | USB_INTS_DEVICE_EVENTS | USB_INTS_ENDPOINT_EVENTS)

void enable_setup_interrupts();
void disable_setup_interrupts();

void enable_buffer_interrupts();
void disable_buffer_interrupts();

void __not_in_flash_func(isr_usbctrl)();

static inline void usb_irq_setup_request();
static inline void usb_irq_bus_reset();
static inline void usb_irq_unhandled();

static inline void __not_in_flash_func(usb_irq_buffer_status)();