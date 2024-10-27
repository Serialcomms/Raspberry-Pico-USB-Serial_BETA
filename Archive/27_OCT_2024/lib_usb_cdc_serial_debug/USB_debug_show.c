
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/regs/usb.h"
#include "hardware/structs/usb.h"
#include "include/USB_setup_packet.h"
#include "include/USB_uart_printf.h"
#include "include/USB_com_port_signalling.h"
#include "include/USB_com_port_framing.h"
#include "include/USB_uart_printf.h"
#include "include/USB_endpoint_struct.h"
#include "include/USB_endpoints_host.h"
#include "include/USB_endpoints_pico.h"
#include "include/USB_buffer_control.h"
#include "include/USB_cdc_line_coding.h"
#include "include/USB_cdc_line_control.h"
#include "include/USB_debug_show.h"

void show_old_line_coding() {

  uart_printf("CDC get line coding, Existing COM Port Settings=%d-%d-%c-%s\n\r",
  pico_com_port.framing.Baud, 
  pico_com_port.framing.Data, 
  parity_text(pico_com_port.framing.Parity), 
  stop_text(pico_com_port.framing.Stop));

}

void show_new_line_coding(uint8_t *data, uint8_t transfer_bytes) {

  port_framing_t *new_line_coding = (port_framing_t *)data;

  uart_printf("CDC get line coding, New COM Port Settings=%d-%d-%c-%s, length=%d\n\r",
  new_line_coding->Baud, 
  new_line_coding->Data, 
  parity_text(new_line_coding->Parity), 
  stop_text(new_line_coding->Stop), 
  transfer_bytes);

}

void show_line_coding_bytes() {

  uint8_t *cdc_line_coding_bytes = (uint8_t *)&pico_com_port.framing;

  uart_printf("Line Coding Bytes (%d) = %02X, %02X, %02X, %02X, %02X, %02X, %02X\n\r", 

  sizeof(pico_com_port.framing),

  cdc_line_coding_bytes[0],
  cdc_line_coding_bytes[1],
  cdc_line_coding_bytes[2],
  cdc_line_coding_bytes[3],
  cdc_line_coding_bytes[4],
  cdc_line_coding_bytes[5],
  cdc_line_coding_bytes[6]);

}

void show_notify_line_state() {

  uart_printf("CDC line state notification on EP3, DTR=%s, RTS=%s\n\r", 
  pico_com_port.signalling.DTE.DTR ? "On" : "Off",  
  pico_com_port.signalling.DTE.RTS ? "On" : "Off");

}

void show_set_line_control(uint8_t interface, uint8_t value) {

  uart_printf("CDC Class SET_LINE_CONTROL_STATE, Interface=%d, Value=%d, DTR=%s, RTS=%s\n\r", 
  interface,  
  value,
  pico_com_port.signalling.DTE.DTR ? "On" : "Off",  
  pico_com_port.signalling.DTE.RTS ? "On" : "Off");
}

void show_send_line_notification() {

  uart_printf(SEPARATOR);
  uart_printf("Sending CDC line state notification on EP3, Request Type=%02X, Data=%04X, DCD=%s, DSR=%s, RI=%s\n\r", 
  cdc_notify_serial_state.request.RequestType,
  cdc_notify_serial_state.data,
  pico_com_port.signalling.DCE.DCD  ? "On" : "Off",  
  pico_com_port.signalling.DCE.DSR  ? "On" : "Off",
  pico_com_port.signalling.DCE.RING ? "On" : "Off");

}

void show_sync_data_packet(uint8_t EP_NUMBER) {

  if (EP_NUMBER) {

    uint8_t *usb_dpram_data = host_endpoint[EP_NUMBER].dpram_address;

    uart_printf("Data Bytes=%02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X\n\r", 
    usb_dpram_data[0x00], usb_dpram_data[0x01], usb_dpram_data[0x02], usb_dpram_data[0x03], 
    usb_dpram_data[0x04], usb_dpram_data[0x05], usb_dpram_data[0x06], usb_dpram_data[0x07]);

  } else {

    uart_printf("Data Bytes=%02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X\n\r", 
    usb_dpram->ep0_buf_a[0],usb_dpram->ep0_buf_a[1],usb_dpram->ep0_buf_a[2],usb_dpram->ep0_buf_a[3],
    usb_dpram->ep0_buf_a[4],usb_dpram->ep0_buf_a[5],usb_dpram->ep0_buf_a[6],usb_dpram->ep0_buf_a[7]);

  }

}

void show_sync_data_packet_to_pico(uint8_t EP_NUMBER) {

  if (EP_NUMBER) {

    uint8_t *usb_dpram_data = pico_endpoint[EP_NUMBER].dpram_address;

    uart_printf("Data Bytes=%02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X\n\r", 
    usb_dpram_data[0x00], usb_dpram_data[0x01], usb_dpram_data[0x02], usb_dpram_data[0x03], 
    usb_dpram_data[0x04], usb_dpram_data[0x05], usb_dpram_data[0x06], usb_dpram_data[0x07]);

  } else {

    uart_printf("Data Bytes=%02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X\n\r", 
    usb_dpram->ep0_buf_a[0],usb_dpram->ep0_buf_a[1],usb_dpram->ep0_buf_a[2],usb_dpram->ep0_buf_a[3],
    usb_dpram->ep0_buf_a[4],usb_dpram->ep0_buf_a[5],usb_dpram->ep0_buf_a[6],usb_dpram->ep0_buf_a[7]);

  }

}

void show_dpram(uint8_t EP_NUMBER, uint8_t *usb_dpram_data) {

    uart_printf("USB DPRAM EP%d Bytes \t01-08 = %02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X \n\r", EP_NUMBER, 
    usb_dpram_data[0x00], usb_dpram_data[0x01], usb_dpram_data[0x02], usb_dpram_data[0x03], 
    usb_dpram_data[0x04], usb_dpram_data[0x05], usb_dpram_data[0x06], usb_dpram_data[0x07]);
}

void show_dpram_ep0() {

  uart_printf("USB DPRAM EP0 Bytes \t01-08 = %02X, %02X, %02X, %02X, %02X, %02X, %02X, %02X \n\r", 
  usb_dpram->ep0_buf_a[0x00], 
  usb_dpram->ep0_buf_a[0x01], 
  usb_dpram->ep0_buf_a[0x02], 
  usb_dpram->ep0_buf_a[0x03], 
  usb_dpram->ep0_buf_a[0x04], 
  usb_dpram->ep0_buf_a[0x05], 
  usb_dpram->ep0_buf_a[0x06], 
  usb_dpram->ep0_buf_a[0x07]
  ); 
}