/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define ZERO_LENGTH_PACKET 0

#define buffer_direction_to_host 0
#define buffer_direction_to_pico 1

#define SEPARATOR "-----------------------------------------------------------------------------------------\n\r"

void show_old_line_coding();
void show_line_coding_bytes();
void show_new_line_coding(uint8_t *data, uint8_t transfer_bytes);

void show_notify_line_state();
void show_set_line_control(uint8_t interface, uint8_t value);
void show_send_line_notification();
void show_dpram(uint8_t EP_NUMBER, uint8_t *usb_dpram_data);
void show_dpram_ep0();
void show_sync_data_packet_to_pico(uint8_t EP_NUMBER);