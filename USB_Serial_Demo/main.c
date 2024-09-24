
/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/printf.h"
#include "pico/util/datetime.h"

#include "hardware/rtc.h"

#include "include/main.h"
#include "lib_usb_cdc_serial/API_usb_serial.h"

#include "include/stdio_tests.h"

datetime_t pico_datetime;

int main() {

    init_main();

    while (true) {

       tight_loop_contents();

    }
}

void init_pico_datetime() {

    pico_datetime.year = 2024;
    pico_datetime.month = 1;
    pico_datetime.day = 1;
    pico_datetime.dotw = 0;
    pico_datetime.hour = 0;
    pico_datetime.min = 0;
    pico_datetime.sec = 0;
  
    rtc_init();

    bool datetime_is_set = rtc_set_datetime(&pico_datetime);

    if (!datetime_is_set) {

        usb_error(USB_ERROR_LEVEL_ERROR);

        busy_wait_ms(5000);

    }

}

static inline void init_main() {

    busy_wait_ms(100);

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1); 

    stdio_deinit_all();
    
    busy_wait_ms(200);

    init_pico_datetime();

    usb_start_serial(true, true);

    clear_screen();

    init_stdio_tests();

    stdio_set_chars_available_callback(vcp_characters_available_callback, NULL);

}

void vcp_characters_available_callback(void* param) {

    (void) param;

}

static inline void clear_screen() {

    printf("\033[H");        // cursor home
    printf("\033[2J");       // clear screen
    printf("\033[3J");       // clear scrollback
    printf("\033[40m");      // black background
    printf("\033[?25l");     // hide cursor (reduce flicker)

}
