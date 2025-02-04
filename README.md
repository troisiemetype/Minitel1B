# Minitel1B_Hard
### Minitel Library for Arduino (with Hardware Serial)

This is a fork from the Minitel library written by Éric Sérandour, which [original repository is here](https://github.com/eserandour/Minitel1B_Hard).  
It allows easy communication with a minitel using its _prise péri-informatique_ (DIN plug), can access every display option available, and read every keyboard key.

I needed to bring some improvement to it :  
- The original library implements 7 bits UART and parity check in software, while most if not all microcontrollers implement it in their hardware UART controllers.  
- Since Espressif has changed the default pins on ESP32, a second constructor was added which enable the choose of RX and TX pins.  
- A constructor was also added to implement RP2040-based boards, like the Rapsberry Pi Pico. On RP2040, _Serial_ are instances of _SerialUART_ instead of _HardwareSerial_.  
- Last but not least, the library now inherits the _Stream_ class, which gives access to all the convenient methods of Arduino from _Stream_ and _Print_ classes, like printing numbers, hexadecimals, write bare characters, or the handy and powerfull _printf()_ when the target architecture implements it (ESP, RP2040, etc.).  

### Boards you can use this libray with.
Altough you can use this library with any Arduino board you have that has a UART controller by wiring the Serial pins to a DIN plug (see readme.txt), some plug-and-play solution exist :  
- [A shield for Arduino Mega / Due](https://entropie.org/3615/index.php/hardware-2023/), with connectors for SD card, RTC module and extension boards, developped by Éric Sérandour.  
- An ESP32 board which you can plug into the Minitel, and is powered by it, [designed by Iodeo, which you can buy on Tindie](https://www.tindie.com/products/iodeo/minitel-esp32-dongle/).  


### Documentation.  

This is the original specification for the Minitel, which has been used to write this library : [Spécifications Techniques d'Utilisation du Minitel 1B](http://543210.free.fr/TV/stum1b.pdf).  

### Revision history

See original repository, or git log, or anotations in files for more information about the revision history of this library.