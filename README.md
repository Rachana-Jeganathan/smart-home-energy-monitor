Smart Home Energy Monitor

This project is a smart home energy monitoring system built with an Arduino Uno, ACS712 current sensor, ESP8266 Wi-Fi module, a 0.96" OLED display, and a microSD card module. It measures real-time current and power consumption of household appliances, displays the data on the OLED, sends it to the Blynk app for remote monitoring, and logs historical data to an SD card for analysis. If power consumption exceeds a set threshold, it alerts the user via the app.
Features

Real-time measurement of current and power consumption.
Local display on a 128x64 OLED screen.
Remote monitoring via the Blynk mobile app.
High consumption alerts through Blynk notifications.
Historical data logging to an SD card (CSV format) for usage analysis.
Sensor calibration for accurate readings.
Deep sleep mode for power efficiency.
Robust error handling for Wi-Fi and sensor issues.

Hardware Requirements

Arduino Uno (or Nano).
ACS712 Current Sensor (5A or 20A version).
ESP8266 Wi-Fi Module (e.g., NodeMCU or ESP-01).
0.96" OLED Display (I2C, 128x64 pixels).
MicroSD Card Module (SPI interface) with a microSD card.
Breadboard and jumper wires.
5V power supply (or USB for Arduino).
10µF capacitor (for ACS712 noise reduction).
Resistors (2.2kΩ and 3.3kΩ for ESP8266 voltage divider).

Software Requirements

Arduino IDE.
Libraries:
Adafruit_GFX
Adafruit_SSD1306
BlynkSimpleEsp8266
SD (for SD card logging)
SPI (for SD card communication)


Blynk mobile app (iOS/Android).


Connections

ACS712:
VCC to Arduino 5V
GND to Arduino GND
OUT to Arduino A0
Add 10µF capacitor across VCC-GND


OLED:
SDA to Arduino A4
SCL to Arduino A5
VCC to 5V
GND to Arduino GND


ESP8266:
TX to Arduino RX (pin 2)
RX to Arduino TX (pin 3) via voltage divider (2.2kΩ and 3.3kΩ)
VCC to 3.3V
GND to Arduino GND


SD Card Module:
CS to Arduino D10
SCK to Arduino D13
MOSI to Arduino D11
MISO to Arduino D12
VCC to 5V
GND to Arduino GND



Setup Instructions

Assemble the Circuit:
Connect the components as per the circuit diagram.
Double-check connections to avoid short circuits.


Install Libraries:
In Arduino IDE, go to Sketch > Include Library > Manage Libraries.
Install Adafruit_GFX, Adafruit_SSD1306, BlynkSimpleEsp8266, SD, and SPI.


Configure Blynk:
Download the Blynk app, create a new project, and note the auth token.
Add gauge widgets for current (V0) and power (V1).


Update Code:
Open energy_monitor.ino in Arduino IDE.
Replace YOUR_BLYNK_AUTH_TOKEN, YOUR_WIFI_SSID, and YOUR_WIFI_PASSWORD with your Blynk token and Wi-Fi credentials.
Adjust voltage (e.g., 220V or 110V) and sensitivity (based on ACS712 model).


Upload Code:
Connect Arduino to your computer and upload the code.


Test:
Power a low-power appliance (e.g., 40W bulb) through the ACS712.
Verify readings on the OLED and Blynk app.
Check the SD card for data.csv to confirm logging.



Usage

The OLED displays current (A), power (W), and a warning if power exceeds 100W.
The Blynk app shows real-time current and power, with push notifications for high consumption.
Historical data is logged to data.csv on the SD card (format: Timestamp,Current (A),Power (W)).
Monitor and optimize appliance usage to reduce energy costs.



Tested with a 40W bulb:
Measured Current: 0.18A
Measured Power: 39.6W
Error: ~1% (compared to expected 40W)



Safety Notes

Use low-power appliances for testing to avoid electrical risks.
For high-power devices, consult an electrician for safe AC interfacing.
Ensure proper polarity and connections to prevent damage to components.

Future Enhancements

Add a supercapacitor for power backup during outages (inspired by my Capacitor-Based Power Backup project).
Integrate with ThingSpeak for cloud-based data analysis.
Support multiple ACS712 sensors for whole-house monitoring.
Add a web dashboard for visualizing historical data.



Built with Arduino, Blynk, and open-source libraries.
Inspired by IoT and energy management solutions.


 
