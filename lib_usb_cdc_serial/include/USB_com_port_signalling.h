/*
 * Copyright (c) 2024 Serialcomms (GitHub).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

typedef struct __packed port_framing {  // must be packed for correct data size = 7 bytes

    uint32_t  Baud;
    uint8_t   Stop;
    uint8_t   Parity;
    uint8_t   Data;

} port_framing_t;

typedef struct DTE_signalling {

    bool DTR;            // Data Terminal Ready
    bool RTS;            // Ready to Send

} DTE_signalling_t;

typedef struct DCE_signalling {

    bool DSR;            // Data Set (modem) Ready
    bool DCD;            // Data Carrier Detect
    bool CTS;            // Clear to Send
    bool RING;           // Ring Signal (dial-up modem)
  
} DCE_signalling_t;

typedef struct port_signalling  {

    DTE_signalling_t DTE;   // terminal e.g. PuTTy on host machine
    DCE_signalling_t DCE;   // 'modem' i.e. Pico as virtual com port    
 
} port_signalling_t;

typedef struct com_port_type {

    port_framing_t framing;
    port_signalling_t signalling;

} com_port_t;

extern com_port_t pico_com_port;

bool com_port_get_dtr();
bool com_port_get_rts();
bool com_port_get_dsr();
bool com_port_get_dcd();

void cdc_class_set_line_break();

void com_port_set_dsr(bool new_state);
void com_port_set_dcd(bool new_state);
void com_port_set_ring(bool new_state);