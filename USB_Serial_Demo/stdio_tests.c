/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/printf.h"
#include "pico/stdio.h"
#include "pico/error.h"
#include "pico/util/datetime.h"
#include "hardware/rtc.h"

#include "include/stdio_tests.h"

#include "lib_usb_cdc_serial/API_usb_serial.h"
#include "lib_usb_cdc_serial/include/USB_descriptor_device.h"

repeating_timer_t stdio_test_loop_timer;

extern datetime_t pico_datetime;

uint16_t test_loop_count;

char TEXT_STRING[20];

uint8_t putty_buffer[128];

static inline void run_test_loop() {

   // stdio_test_1();
   // stdio_test_2();
   // stdio_test_3();
   stdio_test_4();

}

static inline void stdio_test_1() {

    int printf_char;
    static uint8_t test_1_count = 0;  
        
    if (test_1_count) {

        printf_char = getchar_timeout_us(50 * 1000);

        if (printf_char > 0) {
            
            putchar_raw(printf_char & 0x7F);

            ++test_loop_count;
                
        }

    } else {

        rtc_get_datetime(&pico_datetime);
        
        printf("Time=%02d:%02d:%02d, Testing getchar_timeout & putchar_raw\n\r", 
        pico_datetime.hour, pico_datetime.min, pico_datetime.sec);
            
        ++test_1_count;

    }

}

static inline void stdio_test_2() {

   int16_t C;

    rtc_get_datetime(&pico_datetime);
        
    printf("Time=%02d:%02d:%02d, Testing stdio_getchar\n\r", 
    pico_datetime.hour, pico_datetime.min, pico_datetime.sec);

    printf("Enter a Character > ");

    C = getchar_timeout_us(333333);    

    //  C = stdio_getchar(); 

    //  C = getchar();

    //  C = getc(stdin); 

    if (C > -1) {

        uint8_t c = C & 0x7f;

        printf("%c\n\r", c);

        printf("\n\rCharacter Entered=%c, Value=%d\n\r", c, C);

    } else {

        printf("\n\r");
        
        printf("Error = %s\n\r", getchar_text(C));
    }

}

static inline void stdio_test_3() {
    
    rtc_get_datetime(&pico_datetime);
        
    printf("Time=%02d:%02d:%02d, Testing scanf\n\r", 
    pico_datetime.hour, pico_datetime.min, pico_datetime.sec);

    printf("Enter a text string <cr>\n\r");

    printf("> ");

    scanf("%s", TEXT_STRING);

    printf("\n\rString Entered=%s\n\r", TEXT_STRING);

}

static inline void stdio_test_4() {

    int16_t C;
    uint8_t c; 

    rtc_get_datetime(&pico_datetime);
        
    printf("Time=%02d:%02d:%02d, Testing CDC Notify ...\n\r", 
    pico_datetime.hour, pico_datetime.min, pico_datetime.sec);

    printf("Time=%02d:%02d:%02d, R/r to set/clear Ring\n\r", 
    pico_datetime.hour, pico_datetime.min, pico_datetime.sec);

    printf("Time=%02d:%02d:%02d, D/d to set/clear DCD\n\r", 
    pico_datetime.hour, pico_datetime.min, pico_datetime.sec);

    printf("Time=%02d:%02d:%02d, S/s to set/clear DSR\n\r", 
    pico_datetime.hour, pico_datetime.min, pico_datetime.sec);

    printf("Enter set/clear character > ");

    C = getchar();

    if (C > -1) {

        c = C & 0x7f;                
        
        switch (c) {

            case 'R':   set_com_port_ring(true);           break;
            case 'r':   set_com_port_ring(false);          break;
            case 'D':   set_com_port_dcd(true);            break;
            case 'd':   set_com_port_dcd(false);           break;
            case 'S':   set_com_port_dsr(true);            break;
            case 's':   set_com_port_dsr(false);           break;

            default:

            printf("\n\r");
        
            printf("Enter set/clear character R, r, D, d, S, s\n\r");

        }    

        printf("%c\n\r", c);

        printf("\n\rCharacter Entered=%c\n\r", c);

    } else {

        printf("\n\r");
        
        printf("Error = %s\n\r", getchar_text(C));
    }

}


static inline void clear_printf_screen() {
    
    printf("\033[H");        // cursor home
    printf("\033[2J");       // clear screen
    printf("\033[3J");       // clear scrollback
    printf("\033[40m");      // black background
    printf("\033[?25l");     // hide cursor (reduce flicker)
    
}

uint8_t *getchar_text(int16_t character) {

    switch (character) {

        case PICO_ERROR_TIMEOUT:     return "Timeout";
        case PICO_ERROR_NO_DATA:     return "No Data";

        default:                     return "?";
    }

}

void init_stdio_tests() {

    add_repeating_timer_ms(-1000, stdio_test_loop, NULL, &stdio_test_loop_timer);

}

bool stdio_test_loop(repeating_timer_t *stdio_test_loop_timer) {

    if (get_com_port_dtr()) {

        if (test_loop_count) {

            run_test_loop();

        } else {

            clear_printf_screen();

            rtc_get_datetime(&pico_datetime);
            
            printf("Time=%02d:%02d:%02d, Starting stdio test loop\n\r", 
            pico_datetime.hour, pico_datetime.min, pico_datetime.sec);

            printf("Pico Versions, VID=%04X, PID=%04X, USB=%1.2f, Release=%1.2f \n\r", 
            usb_vendor_id(),
            usb_product_id(),
            usb_device_version(),
            usb_device_release()

            );

            ++test_loop_count;
        }           
    }        

    return true;
}
