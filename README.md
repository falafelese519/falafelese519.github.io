# Theft Detection System
 Team Falafel


## Project Overview

Our project is a low cost and small form factor theft detection system for packages delivered. The system can be mounted on any box or package container which has a latching system. 

The system consists of the following components:

- Host QTpy RP2040 which processes incoming sensor data and makes decisions to trigger the solenoid latch or image capture system. 
- Dedicated arduino for keypad password validation
- Solenoid to control the locking mechanism of the box
- ADXL335 IMU to detect a break-in 
- An OLED display for user feedback
- ESP32-CAM camera + WIFI module to send images of the intruder to the server if a break in has been detected.

The RP2040 keeps listening to the accelerometer to detect a break in to the package container and also the password correct/incorrect signal from the keypad password validation subsystem. If the accelerometer data exceeds a threshold or an incorrect password is detected, the camera+wifi subsystem starts capturing images and sends them to the server. If the keypad password is correct, the solenoid is triggered to open the door. 

![image](https://user-images.githubusercontent.com/40466274/210109301-71390730-7c5d-46b5-9818-eed1f7f908ed.png)

![image](https://user-images.githubusercontent.com/40466274/210109313-9160eefe-7971-4d36-b67d-becb070d2b8b.png)

![image](https://user-images.githubusercontent.com/40466274/210109326-b260bde0-934f-436a-a3fd-05535aa4e876.png)

![image](https://user-images.githubusercontent.com/40466274/210109347-f1b767eb-6d4a-4852-a580-e9e526ce380c.png)



## Project instructions:

### 1) Assembly Details: 
Components used: RP 2040, Arduino Uno, ADXL 335 IMU, Adafruit Trellis keypad, ESP32-CAM, I2C OLED Display, solenoid

Connect arduino GPIO password correct GPIO to GPIO4 on RP2040 and password incorrect to GPIO3
Connect the X,Y,Z inputs of ADXL335 to GPIO29, 28, 27 respectively.
Connect default I2C pins of RP2040 to the display I2C pins
Connect GPIO5 of RP2040 to ESP32-CAM
Connect GPIO6 to the SOLENOID

Code can be found at: https://github.com/falafelese519/falafelese519.github.io

### 2) How to set it up: 

Build the c code using cmake. CMAKE file provided in the repo. 
Load the respective .ino files onto ESP32-CAM and arduino. 
Make the connections as described above

### 3) How to operate
Start by entering the correct password on the keypad: Solenoid should unlock
Enter wrong password: Solenoid will lock and your image captured will show up on the firebase server. (See ESP32-CAM code for details)
Violently shake the setup with IMU: Solenoid will lock and your image captured will show up on the firebase server. (See ESP32-CAM code for details)

    

## Project Development Cycle Overview:

### 1) Initial plan: 
We had initially proposed to implement the following:

    1) The camera capture subsystem uses the Pico4ML???s inbuilt camera and a
wifi module to capture and transmit the data.
    2) Theft detection module reads the keypad entry as well as the IMU
sensor data to detect a theft.
    3) The module is mounted on mechanical door/clasp system which is
controlled using a solenoid, triggered by the RPi Pico.
    4) The display provides feedback to the user for password entry, incorrect
attempts and entering into the debug subsystem

### 2) Modifications over time:

    1) We decided to move away from the Pico4ML due to low camera quality and lack of support online compared to RP2040. The system was implemented using the QTPy RP2040 and the camera from the ESP32-CAM module (with integrated WiFi)
    2) We initially planned to use only one central microcontroller to process both sensor inputs as well as actuate the solenoid and wifi module. However, polling on the password entry while maintaining real-time performance to guarantee the safety of the system proved to be a difficult challenge: How to consistently validate password entry while also controlling the rest of the system without running into concurrency issues and delays? So we decided to have a separate processor (arduino) to continuously monitor the password entry and only sends password correct/incorrect to the QTpy2040.
    3) In our initial plan, we wanted to create the physical package holding system using 3D printing. We had to scrap that plan due to lack of time as the time to debug the system took far too long/

    
## Any significant issues you had to troubleshoot, and how you solved them or adapted your plans (including diagrams, REPL sessions, scope traces, etc.)
We faced challenges in uploading a proper image on cloud using Pico4ML and ESP32 Wi-Fi module as they communicate to each other using SPI. To tackle this, we used ESP32-CAM module which supports both Wi-Fi and camera. 

For break-in detection (shaking), we were initially using MPU-6050. We were not able to caliberate it to satisfcation. As a work-around we switched to ADXL-335 for detection. The ADXL335 is a 3-axis analog-output accelerometer with ??3 g measurement range. Using ADXL-335, we were able to easily detect any shaking of the system. 

## Reflections on your design and components/parts you selected, including advantages/disadvantages, whether you would recommend a similar design to future teams, and other design approaches/components you might try next time. Component review: Keypad module:

- Keypad

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Our first choice for a keypad module was a Flat 4x4 Matrix membrane. We found it a little inconvenient to use so we switched to Adafruit &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;NeoTrellis 4x4 Keypad mod&nbsp;&nbsp;&nbsp;ule. Th&nbsp;&nbsp;&nbsp;&nbsp;ese 4x4 button pad boards are fully tile-able and communicate over I2C. The best part is that it &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;provides full color NeoPixel support. We would strongly recommend using an Adafruit NeoTrellis keypad module to future teams.

- Display: 
We used a 0.96-inch OLED for displaying the messages. Our code switches between the following 3 messages: -???Open??? for a correct password entry -???Alert??? on detection of a break-in or shaking of the entire system -???Wrong Pass??? on a wrong password entry.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This OLED satisfied the above display requirements. Unless you want long messages to be displayed, this 0.96-inch display is a perfect &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;choice. Compared to LCD displays OLED is indeed thinner and more efficient. LCDs require backlight whereas OLEDs emit the light &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;themselves with pixels, this one in 128 x 64 pixels to be precise. This allows a thinner build and results in a higher contrast. It is I2C &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;supported.

- Wi-Fi and Camera module: Our original plan was to use Pico4ML for image capture and ESP32 Wi-Fi module for uploading the captured image on Firebase storage. The disadvantage of this choice of components is that one has to establish a communication between Pico4ML and Wi-Fi module through SPI and convert the received data on the Wi-Fi module into a proper image before uploading it to the cloud. On researching, we came across ESP32-CAM by ArduCam. This is a Wi-Fi + Camera module. The board is powered by an ESP32-S SoC from Espressif, a powerful, programmable MCU with out-of-the-box WIFI and Bluetooth. It???s the cheapest (around $7) ESP32 dev board that offers an onboard camera module, MicroSD card support, and 4MB PSRAM at the same time. Since the board does not have a conventional USB port, you will have to use either an FTDI programmer, or an add-on HAT, or an Arduino UNO along with the Arduino IDE/ESP-IDF DEV tools to upload codes to it.

## A bit more detail about some feature or accomplishment you found particularly satisfying.

As we are using a lot of sensors and modules, we did face some challenges in integrating all of them together. But we are satisfied that we were able to integrate everything, and the project turned out as planned and designed. The end to end functioning from detection to image upload along with solenoid latching/unlatching is something we found satisfactory, given that we built it from scratch. Some extra hardware was also used for stepping down the voltage and we also designed a small circuitry for the solenoid to function properly.


## An explanation of the PIO part of your code, including a diagram of the overal logic, as well as an introduction to the RP2040 PIO module and what makes it a unique asset for a microcontroller.

We used PIO for interfacing the 'OLED Display' to RP2040 using I2C protocol.


![Logic_Diagram](https://user-images.githubusercontent.com/114099174/210116627-7e8353af-0950-44cd-aa9d-7b5d89f892ae.png)


The programmable input/output block (PIO) is a versatile hardware interface. It can support a variety of IO standards like I2C, UART, SPI, DSPI, QSPI, 3-pin I2S.
There are two PIO blocks with four state machines each, that can independently execute sequential programs to manipulate GPIOs and transfer data. Unlike a general purpose processor, PIO state machines are highly specialised for IO, with a focus on determinism, precise timing, and close integration with fixed-function hardware. There are 2 identical PIO blocks in RP2040. Each PIO block has dedicated connections to the bus fabric, GPIO and
interrupt controller. . Each state machine is equipped with: </br>
??? Two 32-bit shift registers </br>
??? Two 32-bit scratch registers </br>
??? 4??32-bit bus FIFO in each direction (TX/RX), reconfigurable as 8??32 in a single direction </br>
??? Fractional clock divider </br>
??? Flexible GPIO mapping </br>
??? DMA interface </br>
??? IRQ flag set/clear/status </br>

PIO state machines can be configured and reconfigured dynamically to implement numerous different interfaces.Making state machines programmable in a software-like manner, rather than a fully configurable logic fabric like a CPLD, allows more hardware interfaces to be offered in the same cost and power envelope. This also presents a more familiar programming model, and simpler tool flow, to those who wish to exploit PIO???s full flexibility by programming it directly, rather than using a premade interface from the PIO library. 

PIO is highly performant as well as flexible, due to a carefully selected set of fixed-function hardware inside each state machine.

PIO is a unique asset for a microcontroller because using PIO, one can create one???s own interface from scratch. That way, the issues we face when we try to build a solution around legacy technology or try to use multiple devices (example: SPI) with a single MCU are diminished.


## Team overview
The team consists of:

1) Aamir Abbas Khambaty:
https://github.com/aamirabbaskhambaty

2) Dvisha Bakarania:
https://github.com/dvishab

3) Shantanu Sampath:
https://github.com/Shantykins

