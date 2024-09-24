/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#undef LIB_TINYUSB_HOST
#undef LIB_TINYUSB_DEVICE

uint8_t *getchar_text(int16_t data_byte);

void init_stdio_tests();

static inline void run_test_loop();

static inline void stdio_test_1();
static inline void stdio_test_2();
static inline void stdio_test_3();
static inline void stdio_test_4();

static inline void clear_printf_screen();

bool stdio_test_loop(repeating_timer_t *stdio_test_loop_timer);