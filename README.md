# Gas-Leak-Call-and-Alert-System
This project is an IoT-based gas leakage detection and alert system developed using Arduino. It is designed to monitor the presence of hazardous gases in the environment and trigger real-time alerts to ensure safety.
Project Overview
This project is an IoT-based gas leakage detection and alert system designed to enhance safety by detecting gas leaks and sending notifications via SMS and phone calls. The system uses an Arduino Uno R3 as the microcontroller, interfaced with an MQ-7 gas sensor for detection and a SIM900 GSM/GPRS module for communication. No buzzer is used in this system; alerts are sent exclusively through SMS and calls. The system is powered by a 12V adapter for the SIM900 module and a 5V 2A AC-DC adapter for the Arduino, with connecting cables to establish the circuit.
This repository contains the Arduino code, circuit diagrams, and setup instructions to replicate or extend the gas leakage alert system. The project is ideal for applications in home safety, industrial monitoring, or educational purposes, demonstrating IoT-based remote alerting without auditory alarms.

Components Used
1. Arduino Uno R3 ATmega328P Development Board
The Arduino Uno R3 is the core microcontroller board powering this project. Based on the ATmega328P microcontroller, it provides a robust platform for reading sensor data and controlling the GSM module.

Specifications:

Microcontroller: ATmega328P
Operating Voltage: 5V
Input Voltage (recommended): 7-12V
Digital I/O Pins: 14 (6 support PWM output)
Analog Input Pins: 6
Flash Memory: 32 KB (0.5 KB used by bootloader)
SRAM: 2 KB
EEPROM: 1 KB
Clock Speed: 16 MHz
USB Interface: ATmega16U2 for serial communication


Role in Project: The Arduino Uno R3 reads analog data from the MQ-7 gas sensor to detect gas concentration levels. It processes this data and triggers the SIM900 module to send SMS or make calls when a gas leak is detected (i.e., when the sensor reading exceeds a predefined threshold).
Source: Compatible with Arduino IDE and widely documented for ease of use.

2. SIM900 GPRS/GSM Module
The SIM900 GSM/GPRS module enables cellular communication, allowing the system to send SMS alerts and make phone calls when a gas leak is detected.

Specifications:

Dual-band GSM/GPRS: 900/1800 MHz
Power Supply: 3.4V–4.5V (typically powered via a 5V or 12V adapter, 2A recommended)
Interfaces: TTL UART for communication with Arduino, supports AT commands
Features: SMS, voice calls, GPRS data transmission, low power consumption (1.5mA in sleep mode)
Additional Components: SIM card slot, antenna, and optional CR1220 battery for RTC


Role in Project: When the Arduino detects a gas leak via the MQ-7 sensor, it sends AT commands to the SIM900 module to initiate an SMS or call to a predefined phone number, alerting the user remotely. The module requires a stable power supply (12V, 2A in this project) to handle peak current demands during transmission (up to 2A).
Note: Ensure the SIM card is active, not PIN-locked, and compatible with 2G networks, as the SIM900 does not support 3G or 4G.

3. MQ-7 Gas Sensor
The MQ-7 gas sensor is a semiconductor sensor designed to detect carbon monoxide (CO) and other flammable gases, making it suitable for gas leakage detection.

Specifications:

Detection Range: 10–1000 ppm (CO)
Operating Voltage: 5V
Outputs: Analog output (AO) for variable voltage based on gas concentration, digital output (DO) for threshold-based detection
Heater-Driven: Requires a warm-up period (24–48 hours if unused for over a month) to stabilize readings
Sensitivity: High sensitivity to CO, with adjustable threshold via onboard potentiometer


Role in Project: The MQ-7 sensor’s analog output (AO) is connected to an analog input pin (e.g., A0) on the Arduino. It provides voltage readings proportional to gas concentration. When the reading exceeds a calibrated threshold, the Arduino triggers the SIM900 module to send an alert. The digital output (DO) is not used in this project, as the system relies on analog readings for precise detection.
Calibration Note: The sensor must be calibrated in clean air and known gas concentrations to set accurate thresholds for reliable detection.

4. Connecting Cables

Description: Jumper wires (male-to-male, male-to-female) are used to connect the Arduino, SIM900 module, and MQ-7 sensor, forming the circuit.
Role in Project: These cables ensure reliable connections between components, including:

MQ-7 VCC to Arduino 5V, GND to GND, and AO to an analog pin (e.g., A0).
SIM900 5VT (TX) to Arduino D9, 5VR (RX) to Arduino D10 for serial communication, and power connections to the 12V adapter.


Note: Use high-quality, appropriately rated cables to prevent signal loss or power instability, especially for the SIM900 module’s high-current requirements.

5. 12V Adapter

Description: A 12V DC power adapter with a minimum current rating of 2A, typically connected via a 5.5mm DC jack.
Role in Project: Powers the SIM900 GSM/GPRS module, which requires a stable voltage (3.4V–4.5V internally, achieved via the module’s regulator) and sufficient current to handle peak demands during transmission (up to 2A). The adapter ensures the module operates reliably without resetting, which could occur if powered solely via Arduino’s 5V output.
Note: Always verify the adapter’s compatibility with the SIM900 module’s power requirements and use the module’s power select switch to choose the external power source.

6. 5V 2A AC-DC Adapter

Description: A 5V DC power adapter with a 2A current rating, typically connected to the Arduino via its DC jack or USB port.
Role in Project: Powers the Arduino Uno R3 and the MQ-7 gas sensor, ensuring stable operation. The 5V output is suitable for the Arduino’s recommended input range (7–12V via DC jack, or 5V via USB) and the sensor’s 5V requirement. The 2A rating ensures sufficient current for both components without overloading.
Note: If powering the Arduino via USB, ensure the source (e.g., computer or power bank) can supply at least 1A to avoid instability.


System Functionality

Gas Detection: The MQ-7 sensor continuously monitors the environment for gas leaks (e.g., CO or flammable gases). It outputs an analog voltage to the Arduino, which is proportional to the gas concentration.
Threshold-Based Alerting: The Arduino processes the sensor’s analog readings and compares them to a predefined threshold. If the threshold is exceeded, indicating a gas leak, the Arduino sends AT commands to the SIM900 module.
SMS and Call Alerts: The SIM900 module sends an SMS to a specified phone number with details of the gas leak (e.g., “Gas Leak Detected!”) and/or initiates a phone call to alert the user. No buzzer is used, ensuring silent operation suitable for remote monitoring.
Power Management: The 12V adapter powers the SIM900 module to handle its high current demands, while the 5V 2A adapter powers the Arduino and sensor, ensuring stable operation across all components.
Setup Instructions

Hardware Connections:

Connect the MQ-7 sensor: VCC to Arduino 5V, GND to Arduino GND, AO to Arduino A0.
Connect the SIM900 module: 5VT (TX) to Arduino D9, 5VR (RX) to Arduino D10, GND to Arduino GND, and power to the 12V 2A adapter (ensure the power select switch is set to external power).
Power the Arduino with the 5V 2A adapter via the DC jack or USB.
Insert an active 2G SIM card into the SIM900 module and attach the antenna.


Software Setup:

Install the Arduino IDE and add the SoftwareSerial library.
Download the GPRS_Sim900 library from GitHub and apply any necessary modifications (e.g., for SMS text mode).
Update the code with your phone number and SIM card details (e.g., PIN, if applicable).
Upload the sketch to the Arduino Uno R3 via USB.

Testing:

Power on the system and wait for the SIM900 module to connect to the network (indicated by the network LED blinking every 3 seconds).
Expose the MQ-7 sensor to a small amount of gas (e.g., lighter gas, for testing only) to verify that an SMS or call is triggered.
Monitor the Serial Monitor (9600 baud) for debugging output.
