# USB Serial Port Functions

## start, stop and signal control

API Functions are provided in files `API_usb_serial.c / API_usb_serial.h`

| USB Function                         | Description                                                                                                   |
| ------------------------------------ | --------------------------------------------------------------------------------------------------------------|
| `usb_start_serial(p1, p2, p3)`       | Initialises and starts USB, configures virtual com port driver _(including characters callback)_              |
| `usb_stop_serial()`                  | De-initialises USB, removes device and de-configures virtual com port driver                                  |
| `set_com_port_dcd(bool dcd_state) `  | Sets/clears DATA CARRIER DETECT (DCD) signal from Pico to Host                                                |
| `set_com_port_dsr(bool dsr_state)`   | Sets/clears DATA SET READY (DSR) signal from Pico to Host                                                     |
| `set_com_port_ring(bool ring_state)` | Sets/clears RING INDICATE (RI) signal from Pico to Host                                                       |
| `get_com_port_dtr() `                | Gets DATA TERMINAL READY (DTR) signal from Host                                                               |
| `get_com_port_rts()`                 | Gets READY TO SEND (RTS) signal from Host                                                                     |

* `bool p1 = set cr/lf`

* `bool p2 = set exclusive`

* `bool p3 = enable suspend/resume`


* get functions return `true` or `false` to indicate signal state from host
* set functions should supply `true` or `false` to set / clear signal state
