/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/resets.h"
#include "hardware/regs/usb.h"
#include "hardware/structs/usb.h"
#include "include/USB_bus_reset.h"
#include "include/USB_initialise.h"

void usb_device_init() {
 
    reset_block_num(RESET_USBCTRL);

    unreset_block_num_wait_blocking(RESET_USBCTRL);

    clear_usb_dpsram();

    set_usb_hw_registers();
    
}

void usb_insert_device() {

    clear_sie_status_register();
   
    irq_set_enabled(USBCTRL_IRQ, true);

    irq_set_priority(USBCTRL_IRQ, PICO_HIGHEST_IRQ_PRIORITY);

    usb_hw->sie_ctrl |= USB_SIE_CTRL_PULLUP_EN_BITS;

}

void usb_remove_device() {

    irq_set_enabled(USBCTRL_IRQ, false);

    irq_set_priority(USBCTRL_IRQ, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);

    usb_hw->sie_ctrl &= ~USB_SIE_CTRL_PULLUP_EN_BITS;

}

static inline void clear_usb_dpsram() {

    memset(usb_dpram, 0, sizeof(*usb_dpram)); 

}

static inline void set_usb_hw_registers() {

    usb_hw->main_ctrl = USB_REGISTER_VALUE;   
    usb_hw->sie_ctrl = SIE_REGISTER_VALUE;
    usb_hw->muxing = MUX_REGISTER_VALUE;
    usb_hw->inte = IRQ_REGISTER_VALUE;
    usb_hw->pwr = PWR_REGISTER_VALUE;                  

}