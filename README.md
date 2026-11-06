Plant Monitoring System

An IoT-based plant monitoring prototype built around an ESP8266 NodeMCU. It monitors soil moisture, temperature, humidity and light status, then serves a live dashboard over the local Wi-Fi network.

Hardware

• ESP8266 NodeMCU
• Soil moisture sensor (analog output)
• DHT11 or DHT22 temperature/humidity sensor
• LDR module with digital comparator output
• Breadboard and jumper wires
• USB power supply

Wiring

|NodeMCU pin|Sensor connection                     |
|-----------|--------------------------------------|
|A0         |Soil moisture sensor AOUT             |
|D4 (GPIO2) |DHT data                              |
|D1 (GPIO5) |LDR digital output (optional)         |
|3V3        |Sensor VCC, if supported by the module|
|GND        |Common ground                         |

Analog-input note: The NodeMCU ESP8266 exposes one analog input (A0). The soil sensor and an analog LDR output cannot both be connected directly to A0 at once. This code reads soil moisture on A0 and uses the LDR module’s digital comparator output on D1. Adjust the LDR module’s threshold potentiometer. If you have an analog-only LDR, add an analog multiplexer or external ADC and adapt the code.

Check the voltage range of your particular NodeMCU board and sensor modules before wiring. Do not apply a voltage above the board’s A0 input limit.

Software setup

1. Install Arduino IDE.
2. Install the ESP8266 board package.
3. Select NodeMCU 1.0 (ESP-12E Module).
4. Install DHT sensor library and Adafruit Unified Sensor from Library Manager.
5. Open Arduino/plant_monitor.ino.
6. Enter your Wi-Fi name and password in WIFI_SSID and WIFI_PASSWORD.
7. Select the correct COM/serial port and upload.
8. Open Serial Monitor at 115200 baud. Visit the IP address printed after Wi-Fi connects.

Dashboard endpoints

• / — dashboard page
• /data — JSON sensor readings

The dashboard polls /data every four seconds. Firmware sensor readings are refreshed every two seconds. The low-moisture alert threshold is set to 30%.

Calibration

Set SOIL_DRY and SOIL_WET using readings from your own probe. The supplied values (780 and 320) are example calibration values from the project report and may need adjustment. Verify whether your probe’s ADC reading decreases as it gets wetter; if not, adjust the mapping accordingly.

Project scope

This is a monitoring system. It displays a watering alert but does not automatically operate a pump. Automatic irrigation, cloud notifications, historical logging, multiple plant nodes and predictive watering are possible future enhancements.