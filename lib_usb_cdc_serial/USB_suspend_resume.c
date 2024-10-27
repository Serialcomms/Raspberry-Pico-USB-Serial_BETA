/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/structs/usb.h" 
#include "include/USB_suspend_resume.h"

uint pwm_slice_number;

pwm_config pwm_configuration;

bool USB_DEVICE_SUSPENDED;

extern bool CDC_CONFIGURATION_SET;

void usb_device_suspend_handler() {
	
	bool usb_connected = usb_hw->sie_status & USB_SIE_STATUS_CONNECTED_BITS;

    usb_hardware_clear->sie_status = USB_SIE_STATUS_SUSPENDED_BITS; 

      if (pwm_slice_number && CDC_CONFIGURATION_SET) {

        gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);

        pwm_set_enabled(pwm_slice_number, true);
		
		USB_DEVICE_SUSPENDED = true;

    }
  
}

void usb_device_resume_handler() {
    
    usb_hardware_clear->sie_status = USB_SIE_STATUS_RESUME_BITS;

     if (pwm_slice_number) {

        gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_SIO);

        pwm_set_enabled(pwm_slice_number, false);
		
		USB_DEVICE_SUSPENDED = false;

     }

}

void usb_device_wake_remote_host() {

    usb_hardware_set->sie_ctrl = USB_SIE_CTRL_RESUME_BITS;

}

void usb_device_set_suspend_resume_mode(bool state) {

    if (state) {

        setup_pwm_led_control(state); 

        usb_hardware_set->inte = USB_INTE_DEV_SUSPEND_BITS;

        usb_hardware_set->inte = USB_INTE_DEV_RESUME_FROM_HOST_BITS;

    } else {

        setup_pwm_led_control(state);
      
        usb_hardware_clear->inte = USB_INTE_DEV_SUSPEND_BITS;

        usb_hardware_clear->inte = USB_INTE_DEV_RESUME_FROM_HOST_BITS;

    }

}


// from https://github.com/raspberrypi/pico-examples/blob/master/pwm/led_fade/pwm_led_fade.c

void setup_pwm_led_control(bool led_pwm_state) {
    
    if (led_pwm_state) {

        gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);

        pwm_slice_number = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);

        pwm_clear_irq(pwm_slice_number);

        pwm_set_irq_enabled(pwm_slice_number, true);

        irq_set_exclusive_handler(PWM_DEFAULT_IRQ_NUM(), led_pwm_wrap_handler);

        irq_set_enabled(PWM_DEFAULT_IRQ_NUM(), true);

        pwm_configuration = pwm_get_default_config();

        pwm_config_set_clkdiv(&pwm_configuration, 8.f);
    
        pwm_init(pwm_slice_number, &pwm_configuration, false);

    } else {

        pwm_clear_irq(pwm_slice_number);
        
        pwm_set_irq_enabled(pwm_slice_number, false);
       
        irq_remove_handler(PWM_DEFAULT_IRQ_NUM(), led_pwm_wrap_handler);  

        gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_NULL); 

        pwm_configuration = pwm_get_default_config();
        
        pwm_init(pwm_slice_number, &pwm_configuration, false);

        pwm_config_set_clkdiv(&pwm_configuration, 1.f);

        pwm_slice_number = 0;

    }
}

void led_pwm_wrap_handler() {
    
    static int32_t fade; 
    static uint16_t fade_level;
    static bool fade_direction;

    pwm_clear_irq(pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN));

    if (fade_direction) {

        --fade;

        fade_level = (fade * fade) - 1;

        if (fade_level < 256) fade_direction = !fade_direction;

    } else {

        ++fade;
        
        fade_level = (fade * fade) - 1;

        if (fade_level > 65534) fade_direction = !fade_direction;
    
    }
    
    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, fade_level);
 
}