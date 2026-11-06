/*
  PLANT MONITORING SYSTEM
  Board: NodeMCU ESP8266

  Sensors:
  Soil Moisture -> A0
  DHT11         -> D4
  LDR Digital   -> D1

  Dashboard:
  http://ESP8266-IP/

  JSON Endpoint:
  http://ESP8266-IP/data
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// WiFi Credentials
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Sensor Pins
#define SOIL_PIN A0
#define DHT_PIN D4
#define DHT_TYPE DHT11
#define LDR_PIN D1

// Soil Calibration
const int SOIL_DRY = 780;
const int SOIL_WET = 320;

// Alert Threshold
const int SOIL_ALERT = 30;

// Sensor Refresh Interval
const unsigned long SENSOR_INTERVAL = 2000;

unsigned long lastSensorRead = 0;
unsigned long lastWiFiRetry = 0;

DHT dht(DHT_PIN, DHT_TYPE);
ESP8266WebServer server(80);

// Sensor Variables
float temperatureC = NAN;
float humidity = NAN;

int soilPercent = 0;

String lightStatus = "Unknown";

bool needsWater = false;
bool dhtError = false;


// HTML DASHBOARD
const char DASHBOARD_HTML[] PROGMEM = R"HTML(

<!DOCTYPE html>
<html lang="en">

<head>

<meta charset="UTF-8">

<meta name="viewport"
content="width=device-width, initial-scale=1">

<title>Plant Monitoring System</title>

<style>

:root {
  --green: #246b45;
  --light: #edf7ef;
  --text: #193629;
}

* {
  box-sizing: border-box;
}

body {
  margin: 0;
  padding: 24px;
  font-family: Arial, Helvetica, sans-serif;
  color: var(--text);
  background: var(--light);
}

header {
  text-align: center;
  margin: 8px auto 24px;
}

h1 {
  color: var(--green);
}

.subtitle {
  color: #547263;
}

.grid {
  display: grid;
  grid-template-columns:
    repeat(2, minmax(0, 1fr));
  gap: 16px;
  max-width: 720px;
  margin: auto;
}

.card {
  background: white;
  border-radius: 14px;
  padding: 22px;
  text-align: center;
  box-shadow: 0 3px 12px
    rgba(0,0,0,.08);
}

.label {
  color: #5c7668;
  font-size: 14px;
}

.value {
  color: var(--green);
  font-size: 30px;
  font-weight: bold;
  margin-top: 10px;
}

.status {
  max-width: 720px;
  margin: 18px auto 0;
  padding: 14px;
  border-radius: 10px;
  text-align: center;
  font-weight: bold;
  background: #dff2e4;
  color: #205b35;
}

.alert {
  background: #b83232;
  color: white;
  display: none;
}

.footer {
  text-align: center;
  margin: 18px auto;
  color: #71877b;
  font-size: 12px;
}

@media (max-width: 520px) {

  body {
    padding: 14px;
  }

  .grid {
    grid-template-columns: 1fr;
  }

  .value {
    font-size: 26px;
  }

}

</style>

</head>

<body>

<header>

<h1>🌱 Plant Monitoring System</h1>

<div class="subtitle">
Live IoT Plant Health Dashboard
</div>

</header>

<main class="grid">

<section class="card">

<div class="label">
Soil Moisture
</div>

<div class="value" id="soil">
--%
</div>

</section>


<section class="card">

<div class="label">
Temperature
</div>

<div class="value" id="temp">
-- °C
</div>

</section>


<section class="card">

<div class="label">
Humidity
</div>

<div class="value" id="humidity">
--%
</div>

</section>


<section class="card">

<div class="label">
Light Status
</div>

<div class="value" id="light">
--
</div>

</section>

</main>


<div class="status" id="systemStatus">

Connecting to plant monitor...

</div>


<div class="status alert" id="alertBox">

Soil is dry — water the plant now!

</div>


<div class="footer">

ESP8266 Local Web Dashboard
<br>
Updates every 4 seconds

</div>


<script>

async function updateDashboard() {

  const status =
    document.getElementById(
      'systemStatus'
    );

  try {

    const response = await fetch(
      '/data',
      { cache: 'no-store' }
    );

    if (!response.ok) {
      throw new Error('HTTP error');
    }

    const data = await response.json();

    document.getElementById(
      'soil'
    ).textContent =
      data.soilPercent + '%';

    document.getElementById(
      'temp'
    ).textContent =
      data.temperatureC === null
      ? 'Sensor error'
      : data.temperatureC.toFixed(1) + ' °C';

    document.getElementById(
      'humidity'
    ).textContent =
      data.humidity === null
      ? 'Sensor error'
      : data.humidity.toFixed(1) + '%';

    document.getElementById(
      'light'
    ).textContent =
      data.lightStatus;

    document.getElementById(
      'alertBox'
    ).style.display =
      data.needsWater ? 'block' : 'none';

    status.textContent =
      'Monitoring active · Last updated: ' +
      new Date().toLocaleTimeString();

  }

  catch (error) {

    status.textContent =
      'Unable to receive sensor data. Check connection.';

  }

}

updateDashboard();

setInterval(updateDashboard, 4000);

</script>

</body>

</html>

)HTML";


// READ SOIL MOISTURE
int readSoilMoisture() {

  int raw = analogRead(SOIL_PIN);

  int percentage = map(
    raw,
    SOIL_DRY,
    SOIL_WET,
    0,
    100
  );

  return constrain(
    percentage,
    0,
    100
  );

}


// READ LIGHT STATUS
String readLightStatus() {

  int value = digitalRead(LDR_PIN);

  // Many comparator modules output LOW in bright light.
  // Reverse the labels if your module behaves differently.

  if (value == LOW) {
    return "Bright";
  }

  return "Dim / Dark";

}


// UPDATE SENSOR DATA
void refreshReadings() {

  soilPercent = readSoilMoisture();

  lightStatus = readLightStatus();

  float h = dht.readHumidity();

  float t = dht.readTemperature();

  dhtError = isnan(h) || isnan(t);

  if (!isnan(h)) {
    humidity = h;
  }

  if (!isnan(t)) {
    temperatureC = t;
  }

  needsWater =
    soilPercent < SOIL_ALERT;

}


// FORMAT JSON NUMBERS
String jsonNumber(
  float value,
  int decimals
) {

  if (isnan(value)) {
    return "null";
  }

  return String(value, decimals);

}


// CREATE JSON RESPONSE
String buildJson() {

  String json = "{";

  json += "\"temperatureC\":";
  json += jsonNumber(temperatureC, 1);

  json += ",\"humidity\":";
  json += jsonNumber(humidity, 1);

  json += ",\"soilPercent\":";
  json += String(soilPercent);

  json += ",\"lightStatus\":\"";
  json += lightStatus;
  json += "\"";

  json += ",\"needsWater\":";

  json += needsWater
    ? "true"
    : "false";

  json += ",\"dhtError\":";

  json += dhtError
    ? "true"
    : "false";

  json += "}";

  return json;

}


// DASHBOARD ROUTE
void handleRoot() {

  server.send_P(
    200,
    "text/html",
    DASHBOARD_HTML
  );

}


// JSON ROUTE
void handleData() {

  server.sendHeader(
    "Cache-Control",
    "no-store"
  );

  server.send(
    200,
    "application/json",
    buildJson()
  );

}


// WIFI CONNECTION
void connectToWiFi() {

  WiFi.mode(WIFI_STA);

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  Serial.print(
    "Connecting to WiFi"
  );

  unsigned long startAttempt =
    millis();

  while (
    WiFi.status() != WL_CONNECTED &&
    millis() - startAttempt < 20000
  ) {

    delay(400);

    Serial.print(".");

  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println(
      "WiFi Connected!"
    );

    Serial.print(
      "Dashboard URL: http://"
    );

    Serial.println(
      WiFi.localIP()
    );

  }

  else {

    Serial.println(
      "WiFi connection timed out."
    );

  }

}


// SETUP
void setup() {

  Serial.begin(115200);

  delay(100);

  pinMode(
    SOIL_PIN,
    INPUT
  );

  pinMode(
    LDR_PIN,
    INPUT
  );

  dht.begin();

  connectToWiFi();

  server.on(
    "/",
    HTTP_GET,
    handleRoot
  );

  server.on(
    "/data",
    HTTP_GET,
    handleData
  );

  server.onNotFound(
    []() {
      server.send(
        404,
        "text/plain",
        "Not found"
      );
    }
  );

  server.begin();

  refreshReadings();

  lastSensorRead = millis();

  Serial.println(
    "Plant Monitoring System Started!"
  );

}


// MAIN LOOP
void loop() {

  server.handleClient();


  // SENSOR UPDATE
  if (
    millis() - lastSensorRead >=
    SENSOR_INTERVAL
  ) {

    lastSensorRead = millis();

    refreshReadings();

    Serial.printf(
      "Soil: %d%% | Temp: %.1f C | Humidity: %.1f%% | Light: %s | Water alert: %s\n",
      soilPercent,
      temperatureC,
      humidity,
      lightStatus.c_str(),
      needsWater ? "YES" : "NO"
    );

  }


  // WIFI RECONNECTION
  if (
    WiFi.status() != WL_CONNECTED &&
    millis() - lastWiFiRetry >= 10000
  ) {

    lastWiFiRetry = millis();

    WiFi.disconnect();

    WiFi.begin(
      WIFI_SSID,
      WIFI_PASSWORD
    );

    Serial.println(
      "Retrying WiFi connection..."
    );

  }

}