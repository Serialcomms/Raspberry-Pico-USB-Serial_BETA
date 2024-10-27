/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define usb_hardware_set   ((usb_hw_t *)hw_set_alias_untyped(usb_hw))
#define usb_hardware_clear ((usb_hw_t *)hw_clear_alias_untyped(usb_hw))

void usb_device_resume_handler();
void usb_device_suspend_handler();
void usb_device_wake_remote_host();

void led_pwm_wrap_handler();

void setup_pwm_led_control(bool led_pwm_state);

void usb_device_set_suspend_resume_mode(bool state);