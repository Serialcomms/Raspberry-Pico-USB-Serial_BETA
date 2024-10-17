add_library(lib_usb_cdc_serial INTERFACE)

target_sources(lib_usb_cdc_serial INTERFACE

API_usb_serial.c
USB_EP0_handlers.c 
USB_EP1_handlers.c 
USB_EP3_handlers.c 
USB_buffer_completion.c 
USB_buffer_control.c 
USB_build_endpoints.c 
USB_bus_reset.c
USB_cdc_line_coding.c 
USB_cdc_line_control.c 
USB_com_port_framing.c 
USB_com_port_signalling.c 
USB_data_packet.c 
USB_descriptor_config.c 
USB_descriptor_device.c 
USB_endpoints_host.c 
USB_endpoints_pico.c 
USB_endpoint_control.c
USB_error.c
USB_initialise.c 
USB_interrupts.c
USB_queue_control.c  
USB_queue_receive.c 
USB_queue_transmit.c
USB_set_configuration.c 
USB_setup_address.c 
USB_setup_class_cdc.c
USB_setup_control.c 
USB_setup_descriptors.c 
USB_setup_device.c
USB_setup_endpoint.c
USB_setup_interface.c
USB_setup_packet.c 
USB_setup_strings.c
USB_setup_type_class.c 
USB_setup_type_standard.c
USB_sie_errors.c 
USB_sie_status.c 
USB_vcp.c 
# debug version only below
USB_uart_printf.c 
USB_setup_show.c  
USB_debug_show.c 
)

message("--------------------------------------------------------------")
message("-- Building serialcomms library lib_usb_cdc_serial    (debug) ")
message("--------------------------------------------------------------")
