# LEDCube
Teensy 3.2 driver code for TLC5940 driven 10x10x10 LED cube
## Build
The code can be built by extracting the teensy.zip and running the make file. Use the standard Teensy 3.2 tools to program the hex file. The code in src can also be compiled in the Arduino Teensy environment.
## Interface
Data is communicated to the driver through SPI in packets. First send the rgb color data (3000 bytes) followed by a meta data byte and a sync byte (0x01). The meta data byte should be in the format [xxRS xxBB]. 'R' is the reset flag, 'S' is the standby flag and 'BB' denotes brightness. The sync byte ensures that the data was not corrupted on transfer. Max data transfer speed is 2MHz. Once data is sent, the driver updates after a pause of 2ms. The reset and standby modes can be used to have the driver show a placeholder animation while data is not being transfered.
