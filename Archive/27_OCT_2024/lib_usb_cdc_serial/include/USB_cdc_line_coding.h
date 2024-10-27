/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

void cdc_class_get_line_coding();
void cdc_class_set_line_coding();
void cdc_class_set_default_line_coding();
static inline void cdc_class_send_line_coding_to_host();
static inline void cdc_class_set_new_line_coding(uint8_t *data, uint8_t transfer_bytes);
static inline void set_line_coding_receive_callback(uint8_t *data, uint8_t transfer_bytes);