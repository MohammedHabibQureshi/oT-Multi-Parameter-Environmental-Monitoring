#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

// =============================
// Wi-Fi Configuration
// =============================
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// =============================
// ThingSpeak Configuration
// =============================
const char* THINGSPEAK_SERVER = "http://api.thingspeak.com/update";
const char* API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY";

// =============================
// DHT22 Configuration
// =============================
#define DHT_PIN 4
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

// =============================
// MQ135 Configuration
// =============================
#define MQ135_PIN 34

// =============================
// BMP280 Configuration
// =============================
Adafruit_BMP280 bmp;

// =============================
// Timing
// =============================
unsigned long previousMillis = 0;
const unsigned long interval = 15000;   // 15 seconds


void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("======================================");
  Serial.println(" IoT Environmental Monitoring System ");
  Serial.println("======================================");

  // -----------------------------
  // Initialize DHT22
  // -----------------------------
  dht.begin();

  Serial.println("DHT22 initialized.");

  // -----------------------------
  // Initialize MQ135
  // -----------------------------
  pinMode(MQ135_PIN, INPUT);

  Serial.println("MQ135 initialized.");

  // -----------------------------
  // Initialize BMP280
  // -----------------------------
  if (!bmp.begin(0x76)) {

    Serial.println("BMP280 not detected at 0x76.");

    if (!bmp.begin(0x77)) {
      Serial.println("BMP280 not detected at 0x77.");
      Serial.println("Check BMP280 wiring.");
    }
    else {
      Serial.println("BMP280 detected at address 0x77.");
    }

  }
  else {
    Serial.println("BMP280 detected at address 0x76.");
  }

  // -----------------------------
  // Connect to Wi-Fi
  // -----------------------------
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("System initialization complete.");
}


void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    // ======================================
    // 1. Read DHT22
    // ======================================

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // ======================================
    // 2. Read MQ135
    // ======================================

    int airQuality = analogRead(MQ135_PIN);

    // ======================================
    // 3. Read BMP280
    // ======================================

    float pressure = bmp.readPressure() / 100.0F;

    // ======================================
    // Check DHT22 Reading
    // ======================================

    if (isnan(temperature) || isnan(humidity)) {

      Serial.println("Failed to read data from DHT22.");
      return;
    }

    // ======================================
    // Display Sensor Data
    // ======================================

    Serial.println();
    Serial.println("--------------------------------------");
    Serial.println("Environmental Sensor Readings");
    Serial.println("--------------------------------------");

    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity    : ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("MQ135 Raw   : ");
    Serial.println(airQuality);

    Serial.print("Pressure    : ");
    Serial.print(pressure);
    Serial.println(" hPa");

    // ======================================
    // Upload Data to ThingSpeak
    // ======================================

    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient http;

      String url = String(THINGSPEAK_SERVER);
      url += "?api_key=";
      url += API_KEY;

      url += "&field1=";
      url += String(temperature);

      url += "&field2=";
      url += String(humidity);

      url += "&field3=";
      url += String(airQuality);

      url += "&field4=";
      url += String(pressure);

      Serial.println();
      Serial.println("Uploading data to ThingSpeak...");

      http.begin(url);

      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {

        String response = http.getString();

        Serial.print("HTTP Response Code: ");
        Serial.println(httpResponseCode);

        Serial.print("ThingSpeak Response: ");
        Serial.println(response);

        if (response.toInt() > 0) {
          Serial.println("Data Uploaded to ThingSpeak!");
        }
        else {
          Serial.println("ThingSpeak upload failed.");
        }

      }
      else {

        Serial.print("HTTP Error Code: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    }

    else {

      Serial.println("Wi-Fi disconnected.");
      Serial.println("Attempting to reconnect...");

      WiFi.disconnect();
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }

    Serial.println("--------------------------------------");
  }
}
