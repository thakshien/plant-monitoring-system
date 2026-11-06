# Plant Monitoring System 🌱

An IoT-based plant monitoring system built using ESP8266 NodeMCU. The system monitors soil moisture, temperature, humidity and light intensity, displaying the readings on a live web dashboard.

## Project Details

- Course: 21CSE305P – SerBot: Project-Based Learning in Robotics
- Project: Plant Monitoring System
- Contributors: Ardhiyaksh and A.V.S. Thakshien
- Guide: Dr. R. Kayalvizhi

## Hardware Requirements

- ESP8266 NodeMCU
- Soil Moisture Sensor
- DHT11 / DHT22 Temperature and Humidity Sensor
- LDR Sensor Module
- Breadboard
- Jumper Wires
- USB Power Supply

## Software Requirements

- Arduino IDE
- ESP8266 Board Package
- ESP8266WiFi Library
- ESP8266WebServer Library
- DHT Sensor Library
- HTML, CSS and JavaScript

## Pin Connections

| Component | NodeMCU Pin |
|---|---|
| Soil Moisture Sensor | A0 |
| DHT Sensor | D4 |
| LDR Digital Output | D1 |
| VCC | 3.3V (if supported) |
| GND | GND |

**Note:** ESP8266 NodeMCU has only one analog input (A0). This implementation connects the soil moisture sensor to A0 and uses the LDR module's digital comparator output on D1.

## Features

- Real-time soil moisture monitoring
- Temperature monitoring
- Humidity monitoring
- Light status detection
- Web-based monitoring dashboard
- Automatic sensor data updates
- Low soil moisture alert
- Wi-Fi connectivity

## How It Works

1. Sensors collect environmental data.
2. ESP8266 processes the sensor readings.
3. The ESP8266 connects to a Wi-Fi network.
4. A local web server hosts the dashboard.
5. The dashboard retrieves sensor readings through a JSON endpoint.
6. Users can monitor plant conditions through a browser.

## Installation

1. Install Arduino IDE.
2. Install the ESP8266 board package.
3. Install the DHT Sensor Library and Adafruit Unified Sensor.
4. Open `Arduino/plant_monitor.ino`.
5. Enter your Wi-Fi SSID and password.
6. Upload the code to the NodeMCU.
7. Open Serial Monitor at 115200 baud.
8. Visit the IP address displayed in Serial Monitor.

## Dashboard Endpoints

- `/` – Web dashboard
- `/data` – JSON sensor data

The dashboard refreshes every 4 seconds.

## Soil Moisture Alert

The system displays a watering alert when soil moisture falls below 30%.

## Future Enhancements

- Automatic irrigation system
- Mobile application integration
- Cloud-based monitoring
- Historical sensor data storage
- Multiple plant monitoring

## Project Contributors

- Ardhiyaksh
- A.V.S. Thakshien