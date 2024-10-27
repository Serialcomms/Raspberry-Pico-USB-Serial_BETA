/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/util/queue.h"
#include "include/USB_error.h"
#include "include/USB_data_packet.h"
#include "include/USB_buffer_control.h"
#include "include/USB_setup_control.h"
#include "include/USB_queue_builder.h"
#include "include/USB_queue_control.h"
#include "include/USB_queue_transmit.h"
#include "include/USB_queue_runner.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoint_control.h"

void __not_in_flash_func(start_queue_transfer_to_host)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {

    uint32_t ENDPOINT_TRANSFER_TYPE = get_host_endpoint_transfer_type(EP_NUMBER);
    
    switch (ENDPOINT_TRANSFER_TYPE) {
        
        case USB_TRANSFER_TYPE_BULK:        start_bulk_transfer(EP_NUMBER, source_data, source_data_length);        break;
        case USB_TRANSFER_TYPE_CONTROL:     start_control_transfer(EP_NUMBER, source_data, source_data_length);     break;
        case USB_TRANSFER_TYPE_INTERRUPT:   start_interrupt_transfer(EP_NUMBER, source_data, source_data_length);   break;
        
        default:                            usb_error(USB_ERROR_LEVEL_ERROR);                                       break;
    }
    
}  

static inline void __not_in_flash_func(start_bulk_transfer)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {

    if (source_data_length == 1) {
        
        start_bulk_transfer_single(EP_NUMBER, source_data);
      
    } else {
     
        start_bulk_transfer_multi(EP_NUMBER, source_data, source_data_length);
     
    }    
     
 }
 
 static inline void __not_in_flash_func(start_bulk_transfer_single)(uint8_t EP_NUMBER, const uint8_t *source_data) {
        
    uint8_t *host_endpoint_buffer = get_host_endpoint_dpram_address(EP_NUMBER);
    
    bool ep_idle = get_endpoint_idle_to_host(EP_NUMBER);
     
    if (ep_idle) {

        host_endpoint_buffer[0] = source_data[0];
            
        start_async_send_data_packet(EP_NUMBER, 1);

    } else {
            
        start_bulk_transfer_multi(EP_NUMBER, source_data, 1);
                    
    }           

 }  

  static inline void __not_in_flash_func(start_bulk_transfer_multi)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {
      
    bool queue_capacity = wait_for_queue_capacity_to_host(EP_NUMBER, source_data_length, 5000);
            
    if (queue_capacity) {
                
        add_source_data_to_host_queue(EP_NUMBER, source_data, source_data_length);
        
        bool ep_idle = get_endpoint_idle_to_host(EP_NUMBER);
        
        if (ep_idle) start_queue_runner_to_host(EP_NUMBER);

    } else {
                
         usb_error(USB_ERROR_LEVEL_ERROR);
    }   

 }
 
static inline void start_control_transfer(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {
    
    bool queue_empty = queue_is_empty_to_host(EP_NUMBER);
    
    if (queue_empty) {
        
        add_source_data_to_host_queue(EP_NUMBER, source_data, source_data_length);

        start_queue_runner_to_host(EP_NUMBER);
      
        
    } else {
        
       usb_error(USB_ERROR_LEVEL_ERROR);
    
    }
    
}

static inline void start_interrupt_transfer(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_length) {
	
    uint8_t max_packet_size = get_host_endpoint_max_packet_size(EP_NUMBER);
    uint8_t source_data_bytes = MIN(source_data_length, max_packet_size);
    bool ep_idle = get_endpoint_idle_to_host(EP_NUMBER);
    
    if (ep_idle) {
        
        copy_source_data_to_host_buffer(EP_NUMBER, source_data, source_data_bytes);
        
        if (source_data_bytes) start_async_send_data_packet(EP_NUMBER, source_data_bytes);
        
    } else {
        
        usb_error(USB_ERROR_LEVEL_ERROR);
        
    }

}

static inline void __not_in_flash_func(copy_source_data_to_host_buffer)(uint8_t EP_NUMBER, const uint8_t *source_data, uint16_t source_data_bytes) {
    
    uint16_t buffer_offset = 0;
    uint8_t *host_endpoint_buffer = get_host_endpoint_dpram_address(EP_NUMBER);
    
    do {
        
        host_endpoint_buffer[buffer_offset] = source_data[buffer_offset];
        
    } while (++buffer_offset < source_data_bytes);
}