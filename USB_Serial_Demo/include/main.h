/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#undef LIB_TINYUSB_HOST
#undef LIB_TINYUSB_DEVICE

static inline void init_main();

void init_pico_datetime();

static inline void clear_screen();

extern datetime_t pico_datetime;

void vcp_characters_available_callback(void* param);
