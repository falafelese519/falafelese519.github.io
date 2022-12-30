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

    1) The camera capture subsystem uses the Pico4ML’s inbuilt camera and a
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

## Reflections on your design and components/parts you selected, including advantages/disadvantages, whether you would recommend a similar design to future teams, and other design approaches/components you might try next time.

## A bit more detail about some feature or accomplishment you found particularly satisfying.

## An explanation of the PIO part of your code, including a diagram of the overal logic, as well as an introduction to the RP2040 PIO module and what makes it a unique asset for a microcontroller.
   
 
## Team overview
The team consists of:

1) Aamir Abbas Khambaty:
https://github.com/aamirabbaskhambaty

2) Dvisha Bakarania:
https://github.com/dvishab

3) Shantanu Sampath:
https://github.com/Shantykins

