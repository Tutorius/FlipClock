# FlipClock
A ESP32-clock simulating an old digital clock

Clock-Program with Flip-Digits

This program simulates an old digital clock with flip-digits

It runs on an ESP32 (WROOM-Module)
It runs with a 2,5"-display, resolution 320x240 pixel based on a ST7789-chipset
The display needs to use the color 565-scheme for 16bit-color-adressing.

The display is connected via SPI.
MOSI (SDA) is connected to Port 23
SCLK (SCL) is connected to Port 18
CS is connected to Port 13
DC is connected to Port 14
RST is connected to Port 4

You can change some of these ports, perhaps not all.

The clock needs five push-buttons connected to GND and the port it belongs to

Button 1 : Change Minute-Digit 1 - Port 32
Button 2 : Change Minute-Digit 2 - Port 33
Button 3 : Change Hour-Digit 1 - Port 25
Button 4 : Change Hour-Digit 2 - Port 26
Button 5 : Start Clock - Port 27

Button 6 - Port 15 and Button 7 - Port 16 can be left unconnected, do the same as Button 5

After new start you need to set the time, then press Button 5 to Start the clock

You can change the include-statement for different colors. Put a // in front of the active include and remove
the // in front of your desired color scheme.

The digit-images need much of the flash-memory, so it is possible you need to change the memory-setting.
Use a setting with disable OTA and much program space. (HUGE APP 3MB...)

Enjoy!

Turorius ( https://www.youtube.com/@Tutorius )
