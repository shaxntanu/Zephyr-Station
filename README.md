<div align="center">

# 🌡️ Zephyr Station

### Smart Room Environmental Monitor

[![ESP32](https://img.shields.io/badge/ESP32-Dev%20Module-E7352C?style=flat-square&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D?style=flat-square&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Next.js](https://img.shields.io/badge/Next.js-Dashboard-000000?style=flat-square&logo=next.js&logoColor=white)](https://nextjs.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Active-success?style=flat-square)]()

**A comprehensive IoT environmental monitoring system with multi-sensor support,<br/>real-time visualization, data logging, and intelligent alerts.**

[🚀 Live Dashboard](https://zephyr-station-dashboard.vercel.app) • [📊 Dashboard Repo](https://github.com/shaxntanu/Zephyr-Station-Dashboard) • [📄 Technical Report](https://crocus-zenobia-863.notion.site/Zephyr-Station-Technical-Report-de41e9c0afd3444195afbac904fe2edc?pvs=74)

</div>

---

## 📖 About

Zephyr Station is an advanced environmental monitoring system designed for continuous tracking of indoor air quality, temperature, humidity, and atmospheric pressure. Built with **fault tolerance** in mind, the system continues operating even when individual sensors fail, making it reliable for long-term deployment.

<table>
<tr>
<td width="50%">

### ✨ Key Features

- 🌡️ **Multi-sensor Integration** - 7 sensors & modules
- 📺 **Real-time Display** - Live OLED visualization
- 💾 **Persistent Storage** - Auto CSV logging to SD
- 🔔 **Smart Alerts** - Buzzer for threshold violations
- ⏰ **Accurate Time** - RTC for precise timestamps
- �️ **Faualt Tolerant** - Works with partial failures
- 🌐 **Web Dashboard** - Real-time Next.js interface

</td>
<td width="50%">

### 📊 Monitoring Capabilities

- ✅ Temperature (BME280 + DS18B20 backup)
- ✅ Humidity measurement
- ✅ Atmospheric pressure tracking
- ✅ Air quality sensing (MQ-135)
- ✅ Real-time clock timestamps
- ✅ WiFi connectivity
- ✅ Historical data logging

</td>
</tr>
</table>

---

## 🖥️ Web Dashboard

<div align="center">

**Real-time monitoring and historical data visualization**

[![Live Dashboard](https://img.shields.io/badge/🚀_View_Live_Dashboard-zephyr--station--dashboard.vercel.app-00C7B7?style=for-the-badge)](https://zephyr-station-dashboard.vercel.app)

</div>

<table>
<tr>
<td align="center">📈<br/><b>Interactive Charts</b><br/><sub>Temperature, humidity & AQI graphs</sub></td>
<td align="center">🎛️<br/><b>Real-time Gauges</b><br/><sub>Visual meters for all readings</sub></td>
<td align="center">📋<br/><b>SD Card Viewer</b><br/><sub>Preview logged CSV data</sub></td>
<td align="center">⚠️<br/><b>Alert Config</b><br/><sub>Custom threshold settings</sub></td>
</tr>
</table>

---

## 🛠️ Hardware Components

<details>
<summary><b>📦 Click to expand full components list</b></summary>

| Component | Model/Type | Qty | Purpose |
|:----------|:-----------|:---:|:--------|
| 🎛️ Microcontroller | ESP32 Dev Module | 1 | Main processing unit |
| 📺 Display | 0.96" OLED SSD1306 | 1 | Real-time visualization |
| 🌡️ Environmental | BME280 (I2C) | 1 | Temp, humidity, pressure |
| 🌡️ Temperature | DS18B20 (1-Wire) | 1 | Backup temperature |
| ⏰ Real-Time Clock | DS3231 RTC | 1 | Accurate timekeeping |
| 💾 Storage | MicroSD Module (SPI) | 1 | Data logging |
| 💨 Air Quality | MQ-135 Gas Sensor | 1 | Air quality monitoring |
| 🔔 Buzzer | Active Buzzer 5V | 1 | Audio alerts |
| ⚡ Resistor | 4.7kΩ | 1 | DS18B20 pull-up |
| 🔌 Power | 5V 2A USB | 1 | System power |

</details>

---

## 📡 Pin Configuration

```
┌──────────────────────────────────────────────────────────────┐
│                      ESP32 Pin Mapping                       │
├─────────────────┬─────────────┬──────────────────────────────┤
│    Component    │   GPIO Pin  │            Notes             │
├─────────────────┼─────────────┼──────────────────────────────┤
│ OLED SDA        │     21      │ I2C Bus 0                    │
│ OLED SCL        │     22      │ I2C Bus 0                    │
│ BME280 SDA      │     15      │ I2C Bus 1                    │
│ BME280 SCL      │      2      │ I2C Bus 1                    │
│ DS18B20         │      4      │ 1-Wire (4.7kΩ pull-up)       │
│ RTC SDA         │     13      │ I2C Bus 2                    │
│ RTC SCL         │     14      │ I2C Bus 2                    │
│ SD Card CS      │      5      │ SPI                          │
│ SD Card MOSI    │     23      │ SPI                          │
│ SD Card MISO    │     19      │ SPI                          │
│ SD Card SCK     │     18      │ SPI                          │
│ MQ-135          │     34      │ Analog input                 │
│ Buzzer          │     25      │ Digital output               │
└─────────────────┴─────────────┴──────────────────────────────┘
```

---

## 🚀 Quick Start

### 1️⃣ Clone Repository
```bash
git clone https://github.com/shaxntanu/Zephyr-Station.git
cd Zephyr-Station
```

### 2️⃣ Install Libraries
```
📚 Required Arduino Libraries:
├── Adafruit GFX Library
├── Adafruit SSD1306
├── Adafruit BME280 Library
├── OneWire
├── DallasTemperature
├── RTClib
└── ArduinoJson (for WiFi)
```

### 3️⃣ Upload to ESP32
1. Open `.ino` file in Arduino IDE
2. Select **Board**: `ESP32 Dev Module`
3. Select correct **Port**
4. Click **Upload** ⬆️

### 4️⃣ Connect Dashboard *(Optional)*
```bash
# Edit WiFi credentials in code, then:
cd Zephyr-Station-Dashboard
npm install
npm run dev
```

---

## 📊 Testing Results

<div align="center">

**16-Day Testing Period** • Nov 18 - Dec 3, 2025 • Patiala, India

</div>

| Metric | Average | Range | Data Points |
|:------:|:-------:|:-----:|:-----------:|
| 🌡️ Temperature | **16.7°C** | 15-18°C | 34,560 |
| 💧 Humidity | **80%** | 72-84% | 34,560 |
| 🌀 Pressure | **30.07 inHg** | 30.03-30.16 | 34,560 |
| 💨 Air Quality | **255.2 AQI** | 155-282 | 34,560 |

<div align="center">

**Total: 138,240 data points** • Sampled every 10 seconds

</div>

---

## 🔗 Links

<div align="center">

| Resource | Link |
|:--------:|:----:|
| 🚀 Live Dashboard | [zephyr-station-dashboard.vercel.app](https://zephyr-station-dashboard.vercel.app) |
| 📊 Dashboard Repo | [github.com/shaxntanu/Zephyr-Station-Dashboard](https://github.com/shaxntanu/Zephyr-Station-Dashboard) |
| 📄 Technical Report | [Notion Document](https://crocus-zenobia-863.notion.site/Zephyr-Station-Technical-Report-de41e9c0afd3444195afbac904fe2edc?pvs=74) |

</div>

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

---

<div align="center">

**Made with ❤️ by [Shantanu](https://github.com/shaxntanu)**

⭐ Star this repo if you found it helpful!

</div>
