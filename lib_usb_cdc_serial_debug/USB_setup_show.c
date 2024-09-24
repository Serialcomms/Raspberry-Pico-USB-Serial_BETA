/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "include/USB_uart_printf.h"
#include "include/USB_setup_packet.h"
#include "include/USB_setup_show.h"

void show_setup_packet() {

    uart_printf("Setup IRQ, preparing setup packet, recipient=%d, request=%02X, direction=%d, type=%02X\n\r",  
    setup->recipient, setup->request, setup->direction, setup->request_type >> 5);

    uart_printf("Setup Packet Bytes=%02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X\n\r", 
    setup_packet[0],
    setup_packet[1],
    setup_packet[2],
    setup_packet[3],
    setup_packet[4],
    setup_packet[5],
    setup_packet[6],
    setup_packet[7]
    );
}