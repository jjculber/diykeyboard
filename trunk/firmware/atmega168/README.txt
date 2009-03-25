Some sample code, part of the DIY Keyboard project.  

This directory holds microcontroller code that targets the atmega168, i.e. the chip arduino uses.

To use the makefile, you will need to make sure you have the avr-gcc toolchain installed somewhere, and included in your path.  One way to do this is to install Arduino, and then include something like the following in your .bashrc:

# Add the locations of the arduino, avr tools.
PATH=${PATH}:/Applications/arduino-0011/hardware/tools/avr/bin
PATH=${PATH}:/Applications/arduino-0011/hardware/tools/avr/lib
PATH=${PATH}:/Applications/arduino-0011/hardware/tools/avr/tools

The Makefile currently uses an avrusbtiny programmer to do in-system programming of the chip.
