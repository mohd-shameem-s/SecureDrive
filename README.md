# SecureDrive
Advanced Vehicle Safety and Secure System

**Project Description:**
  The SECURE DRIVE system is designed to provide an integrated solution for enhancing vehicle safety and security. The system combines alcohol detection, PIN 
authentication, and alert mechanisms to ensure that only sober and authorized individuals can operate the vehicle. By using an Arduino microcontroller to integrate various sensors and output devices, the SECURE DRIVE system offers a comprehensive approach to preventing impaired driving and unauthorized vehicle use.
  The alcohol sensor ensures that the vehicle cannot be operated by an intoxicated driver, while the PIN-based authentication system prevents unauthorized access. Realtime feedback through LEDs and a buzzer alerts the driver to the status of the vehicle, enhancing both safety and user experience. This project not only aims to improve road safety by preventing impaired driving but also enhances vehicle security by ensuring only authorized individuals can start the vehicle. 


**Circuit Connections:**
Components Required:
* Arduino Uno R3
* Alcohol sensor (MQ-3 or similar)
* 4x4 Keypad
* Red, Yellow, and Green LEDs
* Buzzer
* L293D motor driver
* 16x2 I2C LCD display
* Resistors (for LEDs and buzzer as needed)
* Power supply components (wires, breadboard, etc.)


**Circuit Diagram:**

**Alcohol Sensor (MQ-3):**
 -> VCC to Arduino 5V
 -> GND to Arduino GND
 -> Analog output to Arduino A0
 
 **4x4 Keypad:**
 -> Connect each keypad pin to Arduino pins (example: rows to pins 6, 7, 8, 9 and columns to pins 10, 11, 12, 13)

**LEDs and Buzzer:**
 -> Red LED: Anode to Arduino pin 3 (through a current-limiting resistor), Cathode to GND
 -> Yellow LED: Anode to Arduino pin 4 (through a current-limiting resistor), Cathode to GND
 -> Green LED: Anode to Arduino pin 5 (through a current-limiting resistor), Cathode to GND
 -> Buzzer: Connect one terminal to Arduino pin 2, and the other terminal to GND
 
**L293D Motor Driver:**
 -> I1 to Arduino pin 8
 -> I2 to Arduino pin 9
 -> I3 to Arduino pin 10
 -> I4 to Arduino pin 11
 -> Enable pins and motor connections as per your motor specifications
 -> 5V and GND to Arduino 5V and GND respectively
 
**I2C LCD Display:**
 -> SDA to Arduino A4
 -> SCL to Arduino A5
 -> VCC and GND to Arduino 5V and GND respectively

 
