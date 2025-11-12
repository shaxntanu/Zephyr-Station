# 🌡️ ESP32 Smart Room Monitor

> A comprehensive IoT environmental monitoring system with multi-sensor support, real-time visualization, data logging, and intelligent alerts.

![ESP32](https://img.shields.io/badge/ESP32-Dev%20Module-blue)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-active-success)

[Report](https://crocus-zenobia-863.notion.site/Zephyr-Station-Technical-Report-de41e9c0afd3444195afbac904fe2edc?pvs=74)

## 🎯 Overview

The ESP32 Smart Room Monitor is an advanced environmental monitoring system designed for continuous tracking of indoor air quality, temperature, humidity, and atmospheric pressure. Built with fault tolerance in mind, the system continues operating even when individual sensors fail, making it reliable for long-term deployment.

### Key Highlights

- **Multi-sensor Integration**: Combines 7 different sensors and modules
- **Real-time Display**: Live data visualization on OLED screen
- **Persistent Storage**: Automatic CSV logging to SD card
- **Intelligent Alerts**: Buzzer notifications for threshold violations
- **Accurate Timekeeping**: RTC module for precise timestamps
- **Fault Tolerant**: Continues operation with partial sensor failures

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
