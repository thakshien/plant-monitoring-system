# plant-monitoring-system
An IoT-based Plant Monitoring System using ESP8266, soil moisture, temperature, humidity and light sensors with a real-time Wi-Fi web dashboard.
🌱 Plant Monitoring System

An IoT-based smart agriculture solution designed to monitor plant health and environmental conditions using sensors and wireless communication.

📌 Overview

The Plant Monitoring System is an IoT-based project that continuously monitors the environmental conditions required for healthy plant growth.

Using an ESP8266 (NodeMCU) microcontroller and multiple sensors, the system collects real-time data about soil moisture, temperature, humidity, and light intensity. The collected information is transmitted over Wi-Fi to a web dashboard, allowing users to monitor plant conditions through a laptop or smartphone.

✨ Features

* Real-time soil moisture monitoring.
* Temperature and humidity monitoring.
* Ambient light intensity detection.
* Wireless data transmission using ESP8266 Wi-Fi.
* Live web dashboard for sensor readings.
* Automatic low-soil-moisture alerts.
* Automatic dashboard updates without page reloads.

🛠️ Hardware Components

Component	Purpose
ESP8266 NodeMCU	Main microcontroller
Soil Moisture Sensor	Measures soil moisture
DHT11 / DHT22	Measures temperature and humidity
LDR Module	Detects light intensity
Breadboard	Circuit prototyping
Jumper Wires	Hardware connections
5V Power Supply	Powers the system

💻 Software and Technologies

* Arduino IDE
* Embedded C/C++
* HTML
* CSS
* JavaScript
* ESP8266WiFi Library
* ESP8266WebServer Library
* Adafruit DHT Sensor Library

⚙️ Working Principle

1. Sensors collect environmental data from the plant surroundings.
2. ESP8266 processes the collected sensor readings.
3. Sensor data is transmitted through a local Wi-Fi network.
4. A web server hosted on the ESP8266 provides sensor data through a JSON endpoint.
5. The web dashboard periodically retrieves and displays updated readings.
6. An alert is displayed whenever soil moisture falls below the configured threshold.

📊 Monitoring Parameters

* Soil Moisture (%)
* Temperature (°C)
* Relative Humidity (%)
* Light Status (Dark / Dim / Bright)

🚀 Getting Started

1. Clone this repository:

git clone https://github.com/YOUR-USERNAME/plant-monitoring-system.git

2. Open the Arduino IDE.
3. Install the ESP8266 board package.
4. Install the required DHT sensor libraries.
5. Open Arduino/plant_monitor.ino.
6. Configure your Wi-Fi credentials.
7. Connect the sensors according to the circuit diagram.
8. Upload the firmware to the ESP8266.
9. Open the IP address displayed in the Serial Monitor using a browser connected to the same Wi-Fi network.

🌍 Applications

* Home gardening
* Greenhouse monitoring
* Small-scale agriculture
* Urban gardening
* Smart agriculture systems

🔮 Future Enhancements

* Automatic irrigation using water pumps.
* Cloud-based monitoring and notifications.
* Historical sensor data logging.
* Multi-plant monitoring.
* Solar-powered deployment.
* Machine-learning-based watering predictions.

👨‍💻 Contributors

* A.V.S. Thakshien
* Ardhiyaksh

📚 Academic Project

21CSE305P – SerBot: Project-Based Learning in Robotics

Department of Networking and Communications
SRM Institute of Science and Technology

⸻

⭐ If you find this project interesting, consider giving this repository a star!