# 🌡️ Zephyr Station (Smart Room Monitor)

> A comprehensive IoT environmental monitoring system with multi-sensor support, real-time visualization, data logging, and intelligent alerts.

![ESP32](https://img.shields.io/badge/ESP32-Dev%20Module-blue)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-active-success)

<p align="center">
  <a href="https://zephyr-station-dashboard.vercel.app">
    <img src="https://img.shields.io/badge/🚀_Live_Dashboard-Vercel-000000?style=for-the-badge&logo=vercel&logoColor=white" alt="Live Dashboard">
  </a>
  <a href="https://github.com/shaxntanu/Zephyr-Station-Dashboard">
    <img src="https://img.shields.io/badge/📊_Dashboard_Repo-GitHub-181717?style=for-the-badge&logo=github&logoColor=white" alt="Dashboard Repo">
  </a>
</p>

#### [📄 Technical Report](https://crocus-zenobia-863.notion.site/Zephyr-Station-Technical-Report-de41e9c0afd3444195afbac904fe2edc?pvs=74)

---

## 🎯 Overview

The ESP32 Smart Room Monitor is an advanced environmental monitoring system designed for continuous tracking of indoor air quality, temperature, humidity, and atmospheric pressure. Built with fault tolerance in mind, the system continues operating even when individual sensors fail, making it reliable for long-term deployment.

### Key Highlights
- **Multi-sensor Integration**: Combines 7 different sensors and modules
- **Real-time Display**: Live data visualization on OLED screen
- **Persistent Storage**: Automatic CSV logging to SD card
- **Intelligent Alerts**: Buzzer notifications for threshold violations
- **Accurate Timekeeping**: RTC module for precise timestamps
- **Fault Tolerant**: Continues operation with partial sensor failures
- **Web Dashboard**: Real-time visualization via [Next.js dashboard](https://github.com/shaxntanu/Zephyr-Station-Dashboard)

---

## 📊 Web Dashboard

The Zephyr Station comes with a companion **Next.js web dashboard** for real-time monitoring and historical data visualization.

<p align="center">
  <a href="https://zephyr-station-dashboard.vercel.app">
    <img src="https://img.shields.io/badge/View_Live_Dashboard-zephyr--station--dashboard.vercel.app-00C7B7?style=for-the-badge" alt="Live Dashboard">
  </a>
</p>

### Dashboard Features
- 📈 **Interactive Charts** - Temperature, humidity, and air quality graphs with Chart.js
- 🎛️ **Real-time Gauges** - Visual meters for all sensor readings
- 📋 **SD Card Log Viewer** - Preview CSV data being logged
- ⚠️ **Alert Configuration** - Set custom thresholds
- 🔧 **Fault Tolerance Demo** - Test sensor failure scenarios
- 📱 **Responsive Design** - Works on mobile, tablet, and desktop

**Dashboard Repository:** [github.com/shaxntanu/Zephyr-Station-Dashboard](https://github.com/shaxntanu/Zephyr-Station-Dashboard)

---

## ✨ Features

### Monitoring Capabilities
- ✅ Temperature monitoring (BME280 + DS18B20 backup)
- ✅ Humidity measurement (BME280)
- ✅ Atmospheric pressure tracking (BME280)
- ✅ Air quality sensing (MQ-135)
- ✅ Real-time clock for accurate timestamping

### System Features
- ✅ OLED display with rotating information screens
- ✅ SD card data logging in CSV format
- ✅ Configurable alert thresholds
- ✅ Audio alerts via buzzer
- ✅ Multiple I2C buses for conflict prevention
- ✅ Graceful handling of sensor failures
- ✅ Low power consumption design
- ✅ WiFi connectivity for dashboard integration

---

## 🛠️ Hardware Requirements

### Components List

| Component | Model/Type | Quantity | Purpose |
|-----------|------------|----------|---------|
| **Microcontroller** | ESP32 Dev Module | 1 | Main processing unit |
| **Display** | 0.96" OLED (SSD1306, 128x64) | 1 | Real-time data visualization |
| **Environmental Sensor** | BME280 (I2C) | 1 | Temp, humidity, pressure |
| **Temperature Sensor** | DS18B20 (1-Wire) | 1 | Backup temperature reading |
| **Real-Time Clock** | DS3231 RTC Module | 1 | Accurate timekeeping |
| **Storage** | MicroSD Card Module (SPI) | 1 | Data logging |
| **Air Quality Sensor** | MQ-135 Gas Sensor | 1 | Air quality monitoring |
| **Buzzer** | Active Buzzer 5V | 1 | Audio alerts |
| **Resistor** | 4.7kΩ | 1 | DS18B20 pull-up |
| **Power Supply** | 5V 2A USB Power | 1 | System power |
| **Breadboard** | Full size (830 points) | 1 | Prototyping |
| **Jumper Wires** | Male-to-Male | 30+ | Connections |
| **SD Card** | 1-32GB MicroSD (FAT32) | 1 | Data storage |

---

## 📡 Pin Configuration

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| OLED SDA | GPIO 21 | I2C Bus 0 |
| OLED SCL | GPIO 22 | I2C Bus 0 |
| BME280 SDA | GPIO 15 | I2C Bus 1 |
| BME280 SCL | GPIO 2 | I2C Bus 1 |
| DS18B20 | GPIO 4 | 1-Wire with 4.7kΩ pull-up |
| RTC SDA | GPIO 13 | I2C Bus 2 |
| RTC SCL | GPIO 14 | I2C Bus 2 |
| SD Card CS | GPIO 5 | SPI |
| SD Card MOSI | GPIO 23 | SPI |
| SD Card MISO | GPIO 19 | SPI |
| SD Card SCK | GPIO 18 | SPI |
| MQ-135 | GPIO 34 | Analog input |
| Buzzer | GPIO 25 | Digital output |

---

## 🚀 Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/shaxntanu/Zephyr-Station.git
cd Zephyr-Station
```

### 2. Install Arduino Libraries
- Adafruit GFX Library
- Adafruit SSD1306
- Adafruit BME280 Library
- OneWire
- DallasTemperature
- RTClib
- ArduinoJson (for WiFi version)

### 3. Upload to ESP32
1. Open the `.ino` file in Arduino IDE
2. Select **Board**: "ESP32 Dev Module"
3. Select the correct **Port**
4. Click **Upload**

### 4. (Optional) Connect to Dashboard
For WiFi connectivity and web dashboard:
1. Edit WiFi credentials in the code
2. Set your computer's IP address
3. Run the [dashboard](https://github.com/shaxntanu/Zephyr-Station-Dashboard) locally or use the [live version](https://zephyr-station-dashboard.vercel.app)

---

## 📊 Testing Results

Data collected during 16-day testing period (Nov 18 - Dec 3, 2025) in Patiala, India:

| Metric | Average | Range |
|--------|---------|-------|
| Temperature | 16.7°C | 15-18°C |
| Humidity | 80% | 72-84% |
| Pressure | 30.07 inHg | 30.03-30.16 inHg |
| Air Quality | 255.2 AQI | 155-282 AQI |

**Total Data Points:** 138,240 (sampled every 10 seconds)

---

## 🔗 Related Links

- **[Live Dashboard](https://zephyr-station-dashboard.vercel.app)** - View the web interface
- **[Dashboard Repository](https://github.com/shaxntanu/Zephyr-Station-Dashboard)** - Next.js dashboard source code
- **[Technical Report](https://crocus-zenobia-863.notion.site/Zephyr-Station-Technical-Report-de41e9c0afd3444195afbac904fe2edc?pvs=74)** - Detailed documentation

---

## 📄 License

MIT License - feel free to use this project for your own environmental monitoring needs!

---

<p align="center">
  Made with ❤️ by <a href="https://github.com/shaxntanu">Shantanu</a>
</p>
