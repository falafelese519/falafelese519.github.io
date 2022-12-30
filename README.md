# falafelese519.github.io


A project showcase (brief project overview with cool photos/videos, probably on your main page).

Project instructions, in enough detail that someone else could re-create your project (components used, assembly details, block diagrams, description of your RP2040 dev environment, links to your code, etc).

Narrative overview of your project's development, and how it evolved from proposal to demo day (showing photos/screenshots/gifs at each stage).
    
Any significant issues you had to troubleshoot, and how you solved them or adapted your plans (including diagrams, REPL sessions, scope traces, etc.)

Reflections on your design and components/parts you selected, including advantages/disadvantages, whether you would recommend a similar design to future teams, and other design approaches/components you might try next time.
Component review:
Keypad module:

Our first choice for a keypad module was a Flat 4x4 Matrix membrane. We found it a little inconvenient to use so we switched to Adafruit NeoTrellis 4x4 Keypad module. 
These 4x4 button pad boards are fully tile-able and communicate over I2C. The best part is that it provides full color NeoPixel support. We would strongly recommend using an Adafruit NeoTrellis keypad module to future teams.

Display:
We used a 0.96-inch OLED for displaying the messages. Our code switches between the following 3 messages:
-“Open” for a correct password entry
-“Alert” on detection of a break-in or shaking of the entire system
-“Wrong Pass” on a wrong password entry

This OLED satisfied the above display requirements. Unless you want long messages to be displayed, this 0.96-inch display is a perfect choice.  Compared to LCD displays OLED is indeed thinner and more efficient. LCDs require backlight whereas OLEDs emit the light themselves with pixels, this one in 128 x 64 pixels to be precise. This allows a thinner build and results in a higher contrast. It is I2C supported.

Wi-Fi and Camera module:
Our original plan was to use Pico4ML for image capture and ESP32 Wi-Fi module for uploading the captured image on Firebase storage. The disadvantage of this choice of components is that one has to establish a communication between Pico4ML and Wi-Fi module through SPI and convert the received data on the Wi-Fi module into a proper image before uploading it to the cloud. 
On researching, we came across ESP32-CAM by ArduCam. This is a Wi-Fi + Camera module. The board is powered by an ESP32-S SoC from Espressif, a powerful, programmable MCU with out-of-the-box WIFI and Bluetooth.
It’s the cheapest (around $7) ESP32 dev board that offers an onboard camera module,  MicroSD card support, and 4MB PSRAM at the same time.
Since the board does not have a conventional USB port, you will have to use either an FTDI programmer, or an add-on HAT, or an Arduino UNO along with the Arduino IDE/ESP-IDF DEV tools to upload codes to it.






A bit more detail about some feature or accomplishment you found particularly satisfying.

An explanation of the PIO part of your code, including a diagram of the overal logic, as well as an introduction to the RP2040 PIO module and what makes it a unique asset for a microcontroller.
   
 
 Team overview (ideally with brief photos/bios, up to you) with links to your individual github accounts or personal pages.

