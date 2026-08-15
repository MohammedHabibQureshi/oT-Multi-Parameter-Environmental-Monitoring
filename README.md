# 🌍 IoT-Based Multi-Parameter Environmental Monitoring System

An ESP32-based IoT system for **real-time environmental monitoring** using multiple sensors and cloud connectivity. The system measures **temperature, relative humidity, atmospheric pressure, and raw MQ135 air-quality sensor response**, then transmits the measurements over Wi-Fi to **ThingSpeak** for remote visualization and historical analysis.

---

## 📌 Overview

Environmental conditions continuously change and can be monitored using distributed sensing devices connected to the Internet of Things (IoT).

This project integrates an **ESP32 microcontroller**, **DHT22**, **MQ135**, and **BMP280** sensors into a compact environmental monitoring node.

The ESP32 acquires sensor measurements, processes the readings, connects to a Wi-Fi network, and sends the collected data to the **ThingSpeak cloud platform using HTTP**.

The uploaded measurements can then be visualized remotely through ThingSpeak dashboards and time-series graphs.

### Parameters Monitored

| Parameter | Sensor | Unit |
|---|---|---|
| Temperature | DHT22 | °C |
| Relative Humidity | DHT22 | % |
| Air-Quality Sensor Response | MQ135 | ADC |
| Atmospheric Pressure | BMP280 | hPa |

> **Important:** The MQ135 implementation reports the sensor's **raw analog response**. It does **not** calculate calibrated gas concentrations in ppm. Accurate ppm estimation requires sensor-specific calibration and environmental compensation.

---

## 🎯 Objectives

The primary objectives of this project are:

1. Monitor multiple environmental parameters using a single IoT node.
2. Measure temperature using the DHT22 sensor.
3. Measure relative humidity using the DHT22 sensor.
4. Acquire the raw analog response of the MQ135 sensor.
5. Measure atmospheric pressure using the BMP280 sensor.
6. Process sensor measurements using an ESP32.
7. Establish wireless connectivity using Wi-Fi.
8. Transmit sensor data using HTTP.
9. Store environmental measurements in the ThingSpeak cloud.
10. Provide remote visualization of collected measurements.
11. Maintain historical environmental data for analysis.
12. Provide a modular architecture that can be extended with additional sensors.

---

# 🏗️ System Architecture

```text
                         ENVIRONMENT
                              │
             ┌────────────────┼────────────────┐
             │                │                │
             ▼                ▼                ▼
          ┌───────┐       ┌───────┐       ┌────────┐
          │ DHT22 │       │ MQ135 │       │ BMP280 │
          └───┬───┘       └───┬───┘       └───┬────┘
              │               │               │
              └───────────────┼───────────────┘
                              │
                              ▼
                       ┌─────────────┐
                       │    ESP32    │
                       │             │
                       │ Sensor      │
                       │ Acquisition │
                       │ Processing  │
                       │ Wi-Fi       │
                       └──────┬──────┘
                              │
                         Wi-Fi / HTTP
                              │
                              ▼
                       ┌─────────────┐
                       │ ThingSpeak  │
                       │    Cloud    │
                       └──────┬──────┘
                              │
                              ▼
                       ┌─────────────┐
                       │   Dashboard │
                       │             │
                       │ Temperature │
                       │ Humidity    │
                       │ MQ135 ADC   │
                       │ Pressure    │
                       └─────────────┘
```

---

# 🔄 End-to-End Data Flow

The complete sensing-to-cloud pipeline is:

```text
Environmental Conditions
          │
          ▼
       Sensors
          │
          ▼
        ESP32
          │
          ├── Sensor Acquisition
          ├── Data Processing
          └── Wi-Fi Communication
          │
          ▼
      HTTP Request
          │
          ▼
      ThingSpeak
          │
          ├── Cloud Storage
          └── Time-Series Data
          │
          ▼
   ThingSpeak Dashboard
          │
          ▼
   Remote Visualization
```

### Data Flow Explanation

1. The sensors interact with the surrounding environment.
2. The DHT22 provides temperature and relative humidity.
3. The MQ135 produces an analog sensor response.
4. The BMP280 measures atmospheric pressure.
5. The ESP32 reads and processes the sensor outputs.
6. The ESP32 connects to the configured Wi-Fi network.
7. Sensor values are sent to ThingSpeak using HTTP.
8. ThingSpeak stores the received measurements.
9. The ThingSpeak dashboard displays the measurements.
10. Historical readings can be analyzed using time-series graphs.

---

# 🔧 Hardware Components

| Component | Function |
|---|---|
| **ESP32** | Main microcontroller, sensor processing, and Wi-Fi communication |
| **DHT22** | Temperature and relative humidity measurement |
| **MQ135** | Raw analog air-quality sensor response |
| **BMP280** | Atmospheric pressure measurement |
| **Breadboard** | Hardware prototyping |
| **Jumper Wires** | Electrical connections |
| **USB Cable** | Programming and power |

---

# 💻 Software & Technologies

| Technology | Purpose |
|---|---|
| **Arduino IDE** | Firmware development and ESP32 programming |
| **Embedded C/C++** | Firmware implementation |
| **ESP32 Arduino Core** | ESP32 development support |
| **Wi-Fi** | Wireless communication |
| **HTTP** | Cloud data transmission |
| **ThingSpeak** | Cloud storage and visualization |

---

# 🌡️ Sensors

## DHT22

The DHT22 is a digital environmental sensor used to measure:

- 🌡️ Temperature
- 💧 Relative humidity

The ESP32 reads both values from the sensor and uploads them to ThingSpeak.

---

## 🌫️ MQ135

The MQ135 is an analog gas/air-quality sensing module.

In the current implementation, the project records:

> **Raw MQ135 ADC response**

The value is treated as a relative sensor response rather than a calibrated gas concentration.

### Why raw ADC?

The relationship between MQ135 sensor output and gas concentration depends on factors such as:

- Sensor calibration
- Sensor preheating
- Load resistance
- Environmental conditions
- Gas composition
- Sensor aging

Therefore, the current implementation does not claim to provide direct ppm measurements.

---

## 🌍 BMP280

The BMP280 is a digital pressure sensor used to measure:

- Atmospheric pressure

The pressure measurement is reported in:

**hPa (hectopascals)**

---

# 🔌 Hardware Connections

The sensor connections should match the GPIO definitions used in the Arduino firmware.

## DHT22

```text
DHT22
├── VCC  → ESP32 3.3V
├── GND  → ESP32 GND
└── DATA → ESP32 GPIO
```

## MQ135

```text
MQ135
├── VCC  → Appropriate Power Supply
├── GND  → ESP32 GND
└── AO   → ESP32 Analog Input
```

## BMP280

```text
BMP280
├── VCC  → ESP32 3.3V
├── GND  → ESP32 GND
├── SDA  → ESP32 SDA
└── SCL  → ESP32 SCL
```

> ⚠️ **Important:** Replace the generic GPIO labels above with the exact pins used by your hardware implementation before treating this README as the final hardware reference.

---

# ☁️ ThingSpeak Configuration

The ThingSpeak channel uses four fields:

| Field | Parameter | Unit |
|---|---|---|
| Field 1 | Temperature | °C |
| Field 2 | Relative Humidity | % |
| Field 3 | MQ135 Raw Response | ADC |
| Field 4 | Atmospheric Pressure | hPa |

Example data mapping:

```text
ThingSpeak Field 1 → Temperature
ThingSpeak Field 2 → Humidity
ThingSpeak Field 3 → MQ135 ADC
ThingSpeak Field 4 → Pressure
```

---

# ⚙️ Working Principle

The system operates according to the following sequence:

```text
1. ESP32 Power-On
       ↓
2. Initialize Sensors
       ↓
3. Connect to Wi-Fi
       ↓
4. Read DHT22
       ↓
5. Read MQ135
       ↓
6. Read BMP280
       ↓
7. Process Sensor Values
       ↓
8. Build HTTP Request
       ↓
9. Send Data to ThingSpeak
       ↓
10. ThingSpeak Stores Data
       ↓
11. Dashboard Displays Data
       ↓
12. Repeat Monitoring Cycle
```

The monitoring cycle continues periodically while the ESP32 remains powered and connected to the network.

---

# 📊 Experimental Results

The prototype demonstrates the complete:

**Sensor → ESP32 → Wi-Fi → HTTP → Cloud → Dashboard**

pipeline.

## Environmental Measurements

The system produces measurements for:

- Temperature
- Relative humidity
- MQ135 raw response
- Atmospheric pressure

### Temperature

Add the measured temperature graph or screenshot here.

```text
screenshots/results/temperature.png
```

### Relative Humidity

Add the measured humidity graph or screenshot here.

```text
screenshots/results/humidity.png
```

### MQ135 Raw Response

Add the MQ135 response graph or screenshot here.

```text
screenshots/results/mq135.png
```

### Atmospheric Pressure

Add the measured pressure graph or screenshot here.

```text
screenshots/results/pressure.png
```

---

# 🖥️ Arduino IDE / Serial Monitor

The ESP32 provides local monitoring through the Arduino IDE Serial Monitor.

Typical output may include:

```text
Connecting to WiFi...
WiFi connected
IP Address: xxx.xxx.xxx.xxx

Temperature: xx.xx °C
Humidity: xx.xx %
MQ135: xxxx
Pressure: xxxx.xx hPa

Sending data to ThingSpeak...
Data uploaded successfully
```

> The exact output depends on the implementation in the `.ino` firmware.

### Serial Monitor Screenshot

Add the actual screenshot:

```text
screenshots/<img width="576" height="405" alt="Serial monitor" src="https://github.com/user-attachments/assets/cb6c3acc-d7b6-4783-b36b-2e55e7c2ed8d" />

```

---

# 📈 ThingSpeak Dashboard

ThingSpeak provides remote visualization of the environmental measurements.

The dashboard can display:

- Temperature trends
- Humidity trends
- MQ135 sensor response
- Atmospheric pressure trends
- Historical time-series measurements

### Dashboard

Add the actual ThingSpeak dashboard screenshot:

```text
screenshots/<img width="575" height="245" alt="Dashboard" src="https://github.com/user-attachments/assets/6fb93751-1133-4b49-bd27-869baf23a779" />

```

### Historical Data

Add the historical graph screenshot:

```text
screenshots/<img width="432" height="192" alt="Historical" src="https://github.com/user-attachments/assets/67aff168-d9c5-43ad-b79f-0a8da6aebc1a" />

```

---

# 📐 System Diagrams

The repository contains the following engineering diagrams:

| Diagram | Description |
|---|---|
| **System Architecture** | Overall system architecture |
| **Hardware Block Diagram** | Hardware components and connections |
| **Software Architecture** | Firmware and cloud software flow |
| **Flowchart** | Program execution flow |
| **Sequence Diagram** | Interaction between system components |
| **Deployment Diagram** | Physical/software deployment structure |

Recommended diagram files:

```text
diagrams/
├── system-architecture.png
├── hardware-block-diagram.png
├── software-architecture.png
├── flowchart.png
├── sequence-diagram.png
└── deployment-diagram.png
```

---

# 📚 Required Arduino Libraries

Install the following libraries through the Arduino IDE Library Manager:

- **DHT sensor library**
- **Adafruit Unified Sensor**
- **Adafruit BMP280 Library**

The ESP32 Arduino Core provides the required functionality for:

- Wi-Fi
- HTTP communication
- ESP32 hardware support

---

# 🛠️ Installation & Setup

## 1. Install Arduino IDE

Install the Arduino IDE on your development computer.

---

## 2. Install ESP32 Board Support

Open:

```text
Arduino IDE
        ↓
File
        ↓
Preferences
        ↓
Additional Boards Manager URLs
```

Add the appropriate ESP32 board package URL.

Then open:

```text
Tools
   ↓
Board
   ↓
Boards Manager
```

Search for:

```text
ESP32
```

and install the ESP32 board package.

---

## 3. Install Required Libraries

Open:

```text
Arduino IDE
      ↓
Library Manager
```

Install:

```text
DHT sensor library
Adafruit Unified Sensor
Adafruit BMP280 Library
```

---

## 4. Connect the Hardware

Connect:

```text
DHT22
MQ135
BMP280
   │
   ▼
ESP32
```

Verify that the GPIO definitions in the firmware match the actual hardware wiring.

---

## 5. Configure Wi-Fi

Open:

```text
IoT_Multi_Parameter_Environmental_Monitoring.ino
```

Configure the Wi-Fi credentials required by the firmware.

> 🔐 **Security:** Do not commit your real Wi-Fi password to GitHub.

A safer approach is to keep credentials in a separate configuration file that is excluded using `.gitignore`.

---

## 6. Configure ThingSpeak

Create a ThingSpeak channel with four fields:

```text
Field 1 → Temperature
Field 2 → Humidity
Field 3 → MQ135 Raw Response
Field 4 → Atmospheric Pressure
```

---

## 7. Add ThingSpeak API Credentials

Configure the ThingSpeak Write API Key in the firmware.

> 🔐 **Security:** Do not publish your actual ThingSpeak Write API Key in a public GitHub repository.

Use a placeholder such as:

```cpp
const char* WRITE_API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY";
```

---

## 8. Select the ESP32 Board

In Arduino IDE:

```text
Tools
   ↓
Board
   ↓
ESP32
   ↓
Select your ESP32 board
```

---

## 9. Select the COM Port

Connect the ESP32 using USB and select the corresponding serial port:

```text
Tools
   ↓
Port
   ↓
COMx
```

---

## 10. Upload the Firmware

Open:

```text
IoT_Multi_Parameter_Environmental_Monitoring.ino
```

Compile and upload the firmware to the ESP32.

---

## 11. Open Serial Monitor

Open:

```text
Tools
   ↓
Serial Monitor
```

Set the baud rate to:

```text
115200
```

Verify:

- Wi-Fi connection
- Sensor initialization
- Sensor measurements
- HTTP transmission
- ThingSpeak response

---

## 12. Verify ThingSpeak Data

Open your ThingSpeak channel and verify that all four fields are receiving data.

The expected pipeline is:

```text
ESP32
  ↓
Wi-Fi
  ↓
HTTP
  ↓
ThingSpeak
  ↓
Fields 1–4
  ↓
Charts
```

---

# 📁 Repository Structure

```text
IoT-Multi-Parameter-Environmental-Monitoring/
│
├── README.md
│
├── IoT_Multi_Parameter_Environmental_Monitoring.ino
│
├── diagrams/
│   ├── system-architecture.png
│   ├── hardware-block-diagram.png<img width="432" height="192" alt="Historical" src="https://github.com/user-attachments/assets/c8e11643-ef89-467b-9e86-ba7c977073f1" />

│   ├── flowchart.png
│   ├── sequence-diagram.png
│
├── screenshots/
│   ├── arduino-output.png
│   ├── serial-monitor.png
│   ├── thingspeak-dashboard.png
│   └── historical-graph.png
│
└── documents/
    ├── Project-Presentation.pptx
    └── Patent-Document.docx
```

---

# 💾 Source Code

The main firmware is:

```text
IoT_Multi_Parameter_Environmental_Monitoring.ino
```

The firmware is responsible for:

- Sensor initialization
- DHT22 temperature measurement
- DHT22 humidity measurement
- MQ135 analog acquisition
- BMP280 pressure measurement
- Wi-Fi connection
- HTTP communication
- ThingSpeak data transmission
- Serial monitoring

---

# 📄 Project Documentation

Additional project documentation is available in the `documents/` directory.

### 📊 Project Documentation

[Project Documents](https://github.com/user-attachments/files/31103707/Enivronmental-project.docx)


### 📄 Project Report

[Project Report](documents/Project-Report.docx)

### 📑 Patent Documentation

[Patent Documentation](https://github.com/user-attachments/files/31103252/Environmental_patent_paper.docx)

> **Note:** If the patent has not been officially filed or granted, describe this as **project patent documentation** rather than claiming that the project has an issued patent.

---

# 🔬 Experimental Implementation

The prototype was implemented using:

- ESP32 development board
- DHT22 temperature and humidity sensor
- MQ135 air-quality sensing module
- BMP280 atmospheric pressure sensor
- Wi-Fi network
- ThingSpeak cloud platform

The implementation demonstrates the complete IoT pipeline:

```text
Physical Environment
        ↓
Environmental Sensors
        ↓
ESP32 Edge Device
        ↓
Wi-Fi Connectivity
        ↓
HTTP Communication
        ↓
ThingSpeak Cloud
        ↓
Data Storage
        ↓
Visualization
```

---

# ⚠️ Limitations

The current implementation has the following limitations:

1. **MQ135 provides raw sensor response rather than calibrated ppm values.**
2. The system currently uses a single ESP32 monitoring node.
3. Cloud transmission depends on Wi-Fi availability.
4. ThingSpeak is used as the cloud monitoring platform.
5. Sensor accuracy depends on sensor characteristics and calibration.
6. The MQ135 requires appropriate calibration for quantitative gas concentration measurement.
7. The prototype does not currently implement automated environmental alerts.
8. The system is not designed as a certified environmental measurement instrument.

---

# 🚀 Future Scope

The system can be extended with:

### Hardware Improvements

- Additional environmental sensors
- CO₂-specific sensors
- PM2.5 / PM10 particulate sensors
- Light intensity sensors
- Soil/environmental sensors
- Multiple ESP32 monitoring nodes

### Software Improvements

- Automated environmental alerts
- Mobile application
- Web-based monitoring dashboard
- Advanced data analytics
- Predictive environmental monitoring
- Machine-learning-based anomaly detection
- Sensor calibration and compensation
- Data export and reporting

### IoT Improvements

- MQTT communication
- Multi-node IoT architecture
- Low-power operation
- Deep-sleep support
- Alternative cloud platforms
- Edge computing

---

# 🔐 Security Considerations

Because the project connects an embedded device to a cloud service, credentials should be handled carefully.

Never commit the following to a public GitHub repository:

```text
Wi-Fi Password
ThingSpeak Write API Key
Private API Credentials
Private Configuration Files
```

Recommended approach:

```text
Firmware
   │
   ├── Public source code
   │
   └── Private configuration
            │
            └── Excluded using .gitignore
```

For a production deployment, additional security mechanisms such as secure credential storage, encrypted communication, device authentication, and certificate validation should be considered.

---

# 📜 Project / Patent Documentation

The project has been documented under the title:

**IoT-Based Multi-Parameter Environmental Monitoring System with Cloud-Enabled Remote Visualization**

The associated documentation is available in:

```text
documents/Patent-Document.docx
```

---

# 📚 References

1. L. Atzori, A. Iera, and G. Morabito, “The Internet of Things: A Survey,” *Computer Networks*, vol. 54, no. 15, pp. 2787–2805, 2010.

2. A. Zanella, N. Bui, A. Castellani, L. Vangelista, and M. Zorzi, “Internet of Things for Smart Cities,” *IEEE Internet of Things Journal*, vol. 1, no. 1, pp. 22–32, 2014.

3. M. Satyanarayanan, “The Emergence of Edge Computing,” *IEEE Computer*, vol. 50, no. 1, pp. 30–39, 2017.

4. Espressif Systems, *ESP32 Series Datasheet*.

5. Espressif Systems, *ESP32 Technical Reference Manual*.

6. Aosong Electronics, *DHT22 Digital Temperature and Humidity Sensor Datasheet*.

7. Hanwei Electronics, *MQ135 Gas Sensor Technical Documentation*.

8. Bosch Sensortec, *BMP280 Digital Pressure Sensor Datasheet*.

9. MathWorks, *ThingSpeak Documentation*.

---

# ⭐ Project Highlights

- ✅ ESP32-based IoT environmental monitoring
- ✅ Multi-parameter environmental sensing
- ✅ DHT22 temperature monitoring
- ✅ DHT22 humidity monitoring
- ✅ MQ135 raw air-quality sensor response
- ✅ BMP280 atmospheric pressure monitoring
- ✅ Wi-Fi connectivity
- ✅ HTTP cloud communication
- ✅ ThingSpeak integration
- ✅ Remote dashboard visualization
- ✅ Historical data visualization
- ✅ Modular sensor architecture
- ✅ Low-cost IoT prototype
- ✅ Cloud-connected environmental monitoring

---

# 👨‍💻 Author

**Mohammed Habib Qureshi**

Internet of Things Student

---

## 📌 Project Summary

This project demonstrates how an ESP32 can act as an IoT edge device that collects environmental measurements from multiple sensors and transmits them to a cloud platform for remote monitoring.

The complete system can be summarized as:

```text
Sensors
   ↓
ESP32
   ↓
Wi-Fi
   ↓
HTTP
   ↓
ThingSpeak
   ↓
Cloud Storage
   ↓
Dashboard
   ↓
Remote Environmental Monitoring
```

The architecture provides a foundation for developing more advanced environmental monitoring systems with **multi-node sensing, edge analytics, machine learning, alerts, mobile applications, and predictive environmental analysis**.
