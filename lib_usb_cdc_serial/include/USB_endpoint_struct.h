/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define DATA_PID_0  0x00000000

#define USB_TRANSFER_TYPE_CONTROL       0x0
#define USB_TRANSFER_TYPE_ISOCHRONOUS   0x1
#define USB_TRANSFER_TYPE_BULK          0x2
#define USB_TRANSFER_TYPE_INTERRUPT     0x3

typedef void (*buffer_completion_handler)(uint8_t EP_NUMBER);
typedef void (*endpoint_callback_handler)(uint8_t *data, int size);

#include "pico/util/queue.h"
#include "USB_queue_builder.h"

struct endpoint_profile {
  
    bool		ep_busy;
	bool        send_ack;
    bool        queue_busy;
    bool        queue_long;
    queue_t     data_queue;
    uint8_t     data_byte;
    uint8_t     transfer_type;
    uint16_t    transfer_bytes;
    uint16_t    max_packet_size;
    uint32_t    next_packet_id;
    
    void        *dpram_address;
     
    buffer_completion_handler endpoint_handler;
    endpoint_callback_handler callback_handler;

};

extern struct endpoint_profile pico_endpoint[];
extern struct endpoint_profile host_endpoint[];