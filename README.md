## USB Serial Device Stack for Raspberry Pico / Pico-W [^3]
### New for 2024, Raspberry Pico SDK Version 2 

This (beta version) repository is intended for anyone :-

* With a general interest in USB CDC/ACM Serial Ports on a Pico device
* Looking for additional serial port functionality - e.g. port signalling DSR/DCD/Ring to host
* Looking for an alternative USB Serial Stack device driver for Pico / Pico-W / Other RP2040 boards

<details><summary>What's New</summary>
<p>

#### 16th October 2024

* functional testing with lurk101/pshell [fork](https://github.com/Serialcomms/pshell-sc)
* fix issues identified by above
* re-arrange endpoints

</p>
</details>  

<details><summary>More Information</summary>
<p>

<details><summary>Design Pattern</summary>
<p>

* Written in C, using Raspberry SDK version 2.0.0
* Bespoke development for Pico and compatible boards only
* All interrupt-driven, no background tasks or timers required
* Uses SDK's queues and stdio_driver for stdio integration
* Library deployment using supplied `CMakeLists.txt` file
* SDK's stdio library `pico_stdio_usb` not required
* Modular design to support future developments

</p>
</details>  

<details><summary>Installing</summary>
<p>

<details><summary>Non-Debug version</summary>
<p>

* Copy directory **`lib_usb_cdc_serial`** to your project directory
* Add **`#include "lib_usb_cdc_serial/API_usb_serial.h"`** to start of your project's `main.c` file
* Add **`set(SKIP_PICO_STDIO_USB 1)`** to your project's `CMakeLists.txt` file, before `pico_sdk_init()`
* Add **`add_subdirectory(lib_usb_cdc_serial)`** to your project's `CMakeLists.txt` file
* Add **`lib_usb_cdc_serial`** to the `target_link_libraries()` section of your project's `CMakeLists.txt`
* Set **`pico_enable_stdio_usb(your_project_name 0)`** in your project's `CMakeLists.txt` file
* Set **`(PICO_SDK_VERSION_STRING VERSION_LESS "2.0.0")`** in your project's `CMakeLists.txt` file
* Add **`usb_start_serial(true, true);` to the `int main()`** section of your project's `main.c` file
* Stub function `void usb_error(uint8_t error_level)` can be used drive error LEDs via GPIO etc. [^2] 
* See [USB Serial Port Functions](documents/functions.md) for functions to add to your program

</p>
</details> 

<details><summary>Debug version</summary>
<p>

#### Important - _Debug needs exclusive access to core 1 and uart0_

##### &emsp; Debug uart_printf statements partially offloaded to core 1
##### &emsp; Normal printf statements processed by stdio / usb serial 

* Copy directory **`lib_usb_cdc_serial_debug`** to your project directory
* Add **`#include "lib_usb_cdc_serial_debug/API_usb_serial.h"`** to start of your project's `main.c` file
* Add **`#include "lib_usb_cdc_serial_debug/include/USB_uart_printf.h"`** to start of your project's `main.c` file
* Add **`set(SKIP_PICO_STDIO_USB 1)`** to your project's `CMakeLists.txt` file, before `pico_sdk_init()`
* Add **`add_subdirectory(lib_usb_cdc_serial_debug)`** to your project's `CMakeLists.txt` file
* Add **`lib_usb_cdc_serial`** to the `target_link_libraries()` section of your project's `CMakeLists.txt`
* Add **`pico_multicore`** to the `target_link_libraries()` section of your project's `CMakeLists.txt`
* Set **`pico_enable_stdio_usb(your_project_name 0)`** in your project's `CMakeLists.txt` file
* Set **`pico_enable_stdio_uart(your_project_name 0)`** in your project's `CMakeLists.txt` file
* Set **`pico_enable_stdio_usb(your_project_name 0)`** in your project's `CMakeLists.txt` file
* Set **`(PICO_SDK_VERSION_STRING VERSION_LESS "2.0.0")`** in your project's `CMakeLists.txt` file
* Add **`initialise_uart_printf();`** to the **`int main()`** section of your project's `main.c` file
* Add **`usb_start_serial(true, true);`** to the **`int main()`** section of your project's `main.c` file

* Stub function `void usb_error(uint8_t error_level)` can be used drive error LEDs via GPIO etc. [^2]
* See [USB Serial Port Functions](documents/functions.md) for functions to add to your program

</p>
</details> 

</p>
</details> 

<details><summary>Issues</summary>
<p>

* USB IRQ5 needs elevated priority for stdin `(getc, scanf etc. )` only - 
* https://github.com/Serialcomms/Raspberry-Pico-USB-Serial_BETA/blob/1bad6c7695f45c752714ae6b47bdccfb00ecb584/lib_usb_cdc_serial/USB_initialise.c#L34
* Elevated IRQ5 priority may not be correct or fully SDK-compliant
  
</p>
</details>  

<details><summary>Testing</summary>
<p>

Works with original Pico, Pico W and other RP2040 boards

#### Client Terminal

&emsp; [CoolTerm](https://freeware.the-meiers.org/) is recommended for signalling testing [DSR/DCD/Ring](screenshots/coolterm_pico.png)

&emsp; [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) is recommended for general [debug](screenshots/PuTTY_debug_probe.png)

<details><summary>USB Enumeration</summary>
<p>  

Pico appears to [enumerate correctly](documents/usb_enumeration.txt) with :-

* Windows host and create a new COM port

* Mac host and create a new `/dev/tty.usbmodem...` device

</p>
</details>    

<details><summary>Pico stdio</summary>
<p>  
 
Pico `stdio` and SDK functions all appear to work as expected, including :-

* `printf();`
* `scanf();`
* `putc();` and variants;
* `getc();` and variants

</p>
</details>  

<details><summary>Test exclusions</summary>
<p>

* Not tested with RP2350 Pico 2
* Not tested for co-existance with other USB stacks[^1]
* Not tested with RTOS or heavily-loaded multicore operation
* Some stdio and port signalling tests are included in the debug demo only

</p>
</details>  

</p>
</details> 

<details><summary>To Do</summary>
<p> 

* Pico 2 testing
* Port Flow Control
* Port signalling handshake
* Error handling improvements
* GPIO LEDS for port signals DSR,DTR,RING etc.
* Other Raspberry & Linux host testing.
* Multiple Com port support

</p>
</details> 
   
<details><summary>Function List</summary>
<p>   

##### USB Functions

&emsp; [USB CDC/ACM Functions](documents/functions.md)

##### SDK stdio

&emsp; SDK function `stdio_set_driver_enabled();` can be used normally if required
   
##### Pico remote reboot

&emsp; Pico can also be rebooted with a Break command from PuTTY or other client

&emsp; `PuTTY > Special Command > Break`

</p>
</details>   

<details><summary>Acknowledgements</summary>  
<p>

* [USB Made Simple](https://www.usbmadesimple.co.uk)
* [USB CDC Class Definitions](https://www.usb.org/document-library/class-definitions-communication-devices-12)
* [Microsoft USB Device Enumeration](https://techcommunity.microsoft.com/t5/microsoft-usb-blog/how-does-usb-stack-enumerate-a-device/ba-p/270685)
* [Microsoft USB Control Transfer](https://learn.microsoft.com/en-us/windows-hardware/drivers/usbcon/usb-control-transfer)
* [USB Descriptor and Request Parser](https://eleccelerator.com/usbdescreqparser/)
* [Thesycon USB Descriptor Dumper](https://www.thesycon.de/eng/usb_descriptordumper.shtml)
* [Ataradov USB Sniffer](https://github.com/ataradov/usb-sniffer-lite)
* [Tana USB Sniffer](https://github.com/tana/pico_usb_sniffer)
* [phind.com](https://phind.com)

</p>
</details>

<details><summary>Glossary</summary>  
<p>

|               |  Description                                  |
| :-----------: | ----------------------------------------------|
| **CDC**       | Communications Device Class (of USB)          |
| **ACM**       | Abstract Control Model (subclass of CDC)      |
| **DSR**       | Data Set Ready                                |
| **DCD**       | Data Carrier Detect                           |

</p>
</details> 

<details><summary>Demo Versions</summary>  
<p>

#### Windows host

&emsp; Check that a COM port is created in Device manager 

&emsp; Use PuTTY or similar client to connect to it.

#### Mac host

&emsp; Check that a `/dev/tty.usbmodem...` is created

&emsp; Use `cu` or similar client to connect to it.

&emsp; e.g. `sudo cu -l /dev/tty/usbmodem1234`


##### Debug Version

&emsp; Shows Enumeration and IRQ activity on Pico `uart0` (via debug probe or similar)

&emsp; Simple menu allows for CDC notification testing - Ring, DCD, DSR 

##### Non-Debug Version

&emsp; Simple menu similar to above 

&emsp; Other tests can be enabled in `stdio_tests.c`

&emsp; No debug output. Stubs can be developed to drive LEDs etc if required.

</p>
</details> 
   
</p>
</details>  


[^1]: May work with PIO/USB Host driver stack
[^2]: Stub only - further development required
[^3]: Beta version as of September 2024

