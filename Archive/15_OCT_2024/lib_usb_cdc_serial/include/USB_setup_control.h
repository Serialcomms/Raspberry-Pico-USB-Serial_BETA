/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define usb_hardware_set   ((usb_hw_t *)hw_set_alias_untyped(usb_hw))
#define usb_hardware_clear ((usb_hw_t *)hw_clear_alias_untyped(usb_hw))

#define ZERO_LENGTH_PACKET 0

void send_zlp_to_host(uint8_t EP_NUMBER);
void receive_zlp_from_host (uint8_t EP_NUMBER);

void end_pico_to_host_control_transfer();

void set_queue_transfer_ack_to_host(uint8_t EP_NUMBER, bool state);

void start_control_transfer_to_host(const void *source_buffer_address, uint8_t source_buffer_length);

void start_control_transfer_receive_callback(void (*callback)(uint8_t *data, uint8_t transfer_bytes), uint8_t expected_bytes);