/*
  ═══════════════════════════════════════════════════════════
  ESP32 Smart Room Monitor - Complete System v1.0
  ═══════════════════════════════════════════════════════════
  
  Project: Zephyr Station Environmental Monitoring System
  Author: Shantanu
  Date: November 2025
  Repository: https://github.com/shaxntanu/Zephyr-Station
  Report: https://crocus-zenobia-863.notion.site/Zephyr-Station-Technical-Report-2a01ebfe2064803aa54ae7de4e927b2c?pvs=73
  
  Description:
  Multi-sensor environmental monitoring system with real-time display,
  data logging, and intelligent alerts. Fault-tolerant design continues
  operation even with partial sensor failures.
  
  Hardware Components:
  - ESP32 Dev Module
  - OLED Display (SSD1306, 128x64)
  - BME280 Environmental Sensor
  - DS18B20 Temperature Sensor
  - RTC DS3231 Real-Time Clock
  - MicroSD Card Module
  - MQ-135 Air Quality Sensor
  - Active Buzzer
  
  License: MIT
  ═══════════════════════════════════════════════════════════
*/

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RTClib.h>

// ═══════════════════════════════════════════════════════════
// PIN CONFIGURATION
// ═══════════════════════════════════════════════════════════

// OLED Display (I2C Bus 0)
#define OLED_ADDR 0x3C
#define OLED_SDA 21
#define OLED_SCL 22

// BME280 Environmental Sensor (I2C Bus 1)
#define BME_SDA 15
#define BME_SCL 2
#define BME_CSE 32  // Chip Select Enable (I2C mode)
#define BME_SDO 33  // Address select (0x76)

// DS18B20 Temperature Sensor (1-Wire)
#define DS18B20_PIN 4

// RTC DS3231 Real-Time Clock (I2C Bus 2)
#define RTC_SDA 13
#define RTC_SCL 14

// SD Card Module (SPI)
#define SD_CS 5
#define SD_MOSI 23
#define SD_MISO 19
#define SD_SCK 18

// MQ-135 Air Quality Sensor (Analog)
#define MQ135_PIN 34

// Buzzer (Digital Output)
#define BUZZER_PIN 25

// ═══════════════════════════════════════════════════════════
// GLOBAL OBJECTS AND VARIABLES
// ═══════════════════════════════════════════════════════════

// I2C Bus instances (separate buses to avoid conflicts)
TwoWire I2C_OLED = TwoWire(0);
TwoWire I2C_BME = TwoWire(1);
TwoWire I2C_RTC = TwoWire(2);

// Device objects
Adafruit_SSD1306 display(128, 64, &I2C_OLED, -1);
Adafruit_BME280 bme;
OneWire oneWire(DS18B20_PIN);
DallasTemperature tempSensor(&oneWire);
RTC_DS3231 rtc;

// Device status flags
bool oledWorking = false;
bool bmeWorking = false;
bool ds18b20Working = false;
bool rtcWorking = false;
bool sdWorking = false;
bool mq135Working = false;
bool buzzerWorking = false;

// Data logging configuration
String logFileName = "/datalog.csv";
unsigned long lastLogTime = 0;
const unsigned long LOG_INTERVAL = 10000; // Log every 10 seconds

// Alert thresholds (adjust as needed)
const int AIR_QUALITY_THRESHOLD = 2000;
const float TEMP_HIGH_THRESHOLD = 35.0;
const float HUMIDITY_HIGH_THRESHOLD = 80.0;
bool alertActive = false;

// ═══════════════════════════════════════════════════════════
// BUZZER CONTROL FUNCTIONS
// ═══════════════════════════════════════════════════════════

void beep(int duration = 100) {
  if (buzzerWorking) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void beepPattern(int count, int duration = 100, int gap = 100) {
  for (int i = 0; i < count; i++) {
    beep(duration);
    if (i < count - 1) delay(gap);
  }
}

void startupSound() {
  beepPattern(3, 100, 100);  // Three quick beeps
}

void alertSound() {
  beepPattern(2, 300, 200);  // Two long beeps
}

void logSound() {
  beep(50);  // Single short beep
}

// ═══════════════════════════════════════════════════════════
// SETUP - INITIALIZE ALL COMPONENTS
// ═══════════════════════════════════════════════════════════

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n╔════════════════════════════════════════════╗");
  Serial.println("║   ESP32 Smart Room Monitor v1.0            ║");
  Serial.println("║   Zephyr Station - Initializing...        ║");
  Serial.println("╚════════════════════════════════════════════╝\n");
  
  // ===== Initialize Buzzer =====
  Serial.print("→ Buzzer (GPIO 25)... ");
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  // Test beep
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  buzzerWorking = true;
  Serial.println("✓ OK");
  delay(300);
  
  // ===== Initialize OLED Display =====
  Serial.print("→ OLED Display (Bus 0, GPIO 21/22)... ");
  I2C_OLED.begin(OLED_SDA, OLED_SCL, 100000);
  
  if(display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    oledWorking = true;
    Serial.println("✓ OK");
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Zephyr Station");
    display.println("Initializing...");
    display.display();
  } else {
    Serial.println("✗ FAILED");
  }
  
  // ===== Initialize BME280 Sensor =====
  Serial.print("→ BME280 Sensor (Bus 1, GPIO 15/2)... ");
  
  // Configure control pins for I2C mode
  pinMode(BME_CSE, OUTPUT);
  pinMode(BME_SDO, OUTPUT);
  digitalWrite(BME_CSE, HIGH);  // Enable I2C mode
  digitalWrite(BME_SDO, LOW);   // Set address to 0x76
  delay(500);
  
  I2C_BME.begin(BME_SDA, BME_SCL, 100000);
  
  if (bme.begin(0x76, &I2C_BME) || bme.begin(0x77, &I2C_BME)) {
    bmeWorking = true;
    Serial.println("✓ OK");
  } else {
    Serial.println("✗ FAILED (Faulty/Not connected)");
  }
  
  if (oledWorking) {
    display.print("BME280: ");
    display.println(bmeWorking ? "OK" : "FAIL");
    display.display();
  }
  
  // ===== Initialize DS18B20 Temperature Sensor =====
  Serial.print("→ DS18B20 Sensor (GPIO 4)... ");
  tempSensor.begin();
  
  if (tempSensor.getDeviceCount() > 0) {
    ds18b20Working = true;
    Serial.println("✓ OK");
  } else {
    Serial.println("✗ FAILED (Faulty/Not connected)");
  }
  
  if (oledWorking) {
    display.print("DS18B20: ");
    display.println(ds18b20Working ? "OK" : "FAIL");
    display.display();
  }
  
  // ===== Initialize RTC DS3231 =====
  Serial.print("→ RTC DS3231 (Bus 2, GPIO 13/14)... ");
  I2C_RTC.begin(RTC_SDA, RTC_SCL, 100000);
  
  if (rtc.begin(&I2C_RTC)) {
    rtcWorking = true;
    Serial.println("✓ OK");
    
    if (rtc.lostPower()) {
      Serial.println("  ⚠ RTC lost power - time needs setting");
      Serial.println("  Uncomment rtc.adjust() line and re-upload");
      // UNCOMMENT BELOW ON FIRST UPLOAD TO SET TIME:
      // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  } else {
    Serial.println("✗ FAILED");
  }
  
  if (oledWorking) {
    display.print("RTC: ");
    display.println(rtcWorking ? "OK" : "FAIL");
    display.display();
  }
  
  // ===== Initialize SD Card =====
  Serial.print("→ SD Card Module (SPI, GPIO 5/18/19/23)... ");
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  
  if (SD.begin(SD_CS)) {
    sdWorking = true;
    Serial.println("✓ OK");
    
    // Create log file with header if doesn't exist
    if (!SD.exists(logFileName.c_str())) {
      File logFile = SD.open(logFileName.c_str(), FILE_WRITE);
      if (logFile) {
        logFile.println("DateTime,BME_Temp,BME_Humidity,BME_Pressure,DS18_Temp,AirQuality,Alert");
        logFile.close();
        Serial.println("  ✓ Created new log file with header");
      }
    } else {
      Serial.println("  ✓ Existing log file found");
    }
    
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.print("  Card Size: ");
    Serial.print(cardSize);
    Serial.println(" MB");
  } else {
    Serial.println("✗ FAILED (Check card/wiring)");
  }
  
  if (oledWorking) {
    display.print("SD Card: ");
    display.println(sdWorking ? "OK" : "FAIL");
    display.display();
  }
  
  // ===== Initialize MQ-135 Air Quality Sensor =====
  Serial.print("→ MQ-135 Air Quality (GPIO 34)... ");
  pinMode(MQ135_PIN, INPUT);
  
  int testValue = analogRead(MQ135_PIN);
  if (testValue > 0 && testValue < 4095) {
    mq135Working = true;
    Serial.print("✓ OK (Reading: ");
    Serial.print(testValue);
    Serial.println(")");
    Serial.println("  ⚠ Sensor needs 24-48h preheat for accuracy");
  } else {
    Serial.println("✗ FAILED (Not connected)");
  }
  
  if (oledWorking) {
    display.print("MQ-135: ");
    display.println(mq135Working ? "OK" : "FAIL");
    display.display();
  }
  
  // ===== System Status Summary =====
  delay(1000);
  Serial.println("\n════════════════════════════════════════════");
  Serial.println("SYSTEM STATUS SUMMARY");
  Serial.println("════════════════════════════════════════════");
  Serial.printf("%-15s %s\n", "OLED Display:", oledWorking ? "✓ Working" : "✗ Failed");
  Serial.printf("%-15s %s\n", "BME280:", bmeWorking ? "✓ Working" : "✗ Failed");
  Serial.printf("%-15s %s\n", "DS18B20:", ds18b20Working ? "✓ Working" : "✗ Failed");
  Serial.printf("%-15s %s\n", "RTC DS3231:", rtcWorking ? "✓ Working" : "✗ Failed");
  Serial.printf("%-15s %s\n", "SD Card:", sdWorking ? "✓ Working" : "✗ Failed");
  Serial.printf("%-15s %s\n", "MQ-135:", mq135Working ? "✓ Working" : "✗ Failed");
  Serial.printf("%-15s %s\n", "Buzzer:", buzzerWorking ? "✓ Working" : "✗ Failed");
  
  int workingCount = (oledWorking?1:0) + (bmeWorking?1:0) + (ds18b20Working?1:0) + 
                     (rtcWorking?1:0) + (sdWorking?1:0) + (mq135Working?1:0) + (buzzerWorking?1:0);
  
  Serial.println("════════════════════════════════════════════");
  Serial.printf("Working Devices: %d/7\n", workingCount);
  Serial.println("════════════════════════════════════════════\n");
  
  Serial.println("Alert Thresholds:");
  Serial.printf("  Temperature: > %.1f°C\n", TEMP_HIGH_THRESHOLD);
  Serial.printf("  Air Quality: > %d PPM\n", AIR_QUALITY_THRESHOLD);
  Serial.printf("  Humidity: > %.1f%%\n\n", HUMIDITY_HIGH_THRESHOLD);
  
  Serial.println("System Ready! Monitoring started...\n");
  
  // Play startup sound
  if (buzzerWorking) {
    startupSound();
  }
  
  // Show ready screen on OLED
  if (oledWorking) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("=== READY ===");
    display.println();
    display.printf("Active: %d/7\n", workingCount);
    display.println();
    display.println("Monitoring...");
    display.display();
    delay(2000);
  }
}

// ═══════════════════════════════════════════════════════════
// MAIN LOOP - CONTINUOUS MONITORING
// ═══════════════════════════════════════════════════════════

void loop() {
  // Get current time from RTC
  DateTime now;
  if (rtcWorking) {
    now = rtc.now();
  }
  
  // Read all sensors
  float bmeTemp = 0.0, bmeHumidity = 0.0, bmePressure = 0.0;
  float ds18Temp = 0.0;
  int airQuality = 0;
  
  // Read BME280 (Temperature, Humidity, Pressure)
  if (bmeWorking) {
    bmeTemp = bme.readTemperature();
    bmeHumidity = bme.readHumidity();
    bmePressure = bme.readPressure() / 100.0F;  // Convert to hPa
  }
  
  // Read DS18B20 (Backup temperature sensor)
  if (ds18b20Working) {
    tempSensor.requestTemperatures();
    ds18Temp = tempSensor.getTempCByIndex(0);
  }
  
  // Read MQ-135 (Air quality)
  if (mq135Working) {
    airQuality = analogRead(MQ135_PIN);
  }
  
  // ===== Check Alert Conditions =====
  bool shouldAlert = false;
  String alertReason = "";
  
  // Air quality alert
  if (mq135Working && airQuality > AIR_QUALITY_THRESHOLD) {
    shouldAlert = true;
    alertReason = "High Air Pollution";
  }
  
  // Temperature alert
  if (bmeWorking && bmeTemp > TEMP_HIGH_THRESHOLD) {
    shouldAlert = true;
    if (alertReason != "") alertReason += " / ";
    alertReason += "High Temperature";
  }
  
  // Humidity alert
  if (bmeWorking && bmeHumidity > HUMIDITY_HIGH_THRESHOLD) {
    shouldAlert = true;
    if (alertReason != "") alertReason += " / ";
    alertReason += "High Humidity";
  }
  
  // Trigger alert sound
  if (shouldAlert && !alertActive) {
    alertActive = true;
    if (buzzerWorking) {
      alertSound();
    }
    Serial.printf("⚠⚠⚠ ALERT TRIGGERED: %s\n", alertReason.c_str());
  } else if (!shouldAlert) {
    alertActive = false;
  }
  
  // ===== Update OLED Display =====
  if (oledWorking) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    
    // Display time header
    if (rtcWorking) {
      display.print("=== ");
      if(now.hour() < 10) display.print("0");
      display.print(now.hour());
      display.print(":");
      if(now.minute() < 10) display.print("0");
      display.print(now.minute());
      display.print(":");
      if(now.second() < 10) display.print("0");
      display.print(now.second());
      display.println(" ===");
    } else {
      display.println("=== --:--:-- ===");
    }
    
    // Display sensor readings
    display.print("T:");
    display.print(bmeWorking ? String(bmeTemp, 1)+"C" : "---");
    display.print(" H:");
    display.println(bmeWorking ? String((int)bmeHumidity)+"%" : "---");
    
    display.print("P:");
    display.print(bmeWorking ? String((int)bmePressure)+"hPa" : "----");
    display.println();
    
    display.print("Air: ");
    if (mq135Working) {
      display.print(airQuality);
      display.println(airQuality > AIR_QUALITY_THRESHOLD ? " ⚠" : " OK");
    } else {
      display.println("---");
    }
    
    display.println();
    
    // Display alert or status
    if (shouldAlert) {
      display.setTextSize(1);
      display.println("⚠ ALERT!");
      // Display alert reason (truncate if too long)
      if (alertReason.length() > 21) {
        display.println(alertReason.substring(0, 21));
      } else {
        display.println(alertReason);
      }
    } else {
      display.print("SD:");
      display.print(sdWorking ? "Log" : "Off");
      display.print(" RTC:");
      display.println(rtcWorking ? "OK" : "?");
    }
    
    display.display();
  }
  
  // ===== Serial Output =====
  if (rtcWorking) {
    Serial.print(now.timestamp(DateTime::TIMESTAMP_FULL));
    Serial.print(" | ");
  } else {
    Serial.print("NO-RTC | ");
  }
  
  Serial.print("T:");
  Serial.print(bmeWorking ? String(bmeTemp,1)+"C" : "---");
  Serial.print(" H:");
  Serial.print(bmeWorking ? String((int)bmeHumidity)+"%" : "---");
  Serial.print(" P:");
  Serial.print(bmeWorking ? String((int)bmePressure)+"hPa" : "---");
  Serial.print(" Air:");
  Serial.print(mq135Working ? String(airQuality) : "---");
  
  if (shouldAlert) {
    Serial.print(" | ⚠ ALERT: ");
    Serial.print(alertReason);
  }
  
  Serial.println();
  
  // ===== Log Data to SD Card =====
  if (sdWorking && millis() - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = millis();
    
    File logFile = SD.open(logFileName.c_str(), FILE_APPEND);
    if (logFile) {
      // Write timestamp
      if (rtcWorking) {
        logFile.print(now.timestamp(DateTime::TIMESTAMP_FULL));
      } else {
        logFile.print("NO_RTC");
      }
      logFile.print(",");
      
      // Write sensor data
      logFile.print(bmeWorking ? String(bmeTemp, 2) : "0.0");
      logFile.print(",");
      logFile.print(bmeWorking ? String(bmeHumidity, 1) : "0.0");
      logFile.print(",");
      logFile.print(bmeWorking ? String(bmePressure, 1) : "0.0");
      logFile.print(",");
      logFile.print(ds18b20Working ? String(ds18Temp, 2) : "0.0");
      logFile.print(",");
      logFile.print(mq135Working ? String(airQuality) : "0");
      logFile.print(",");
      logFile.println(shouldAlert ? alertReason : "OK");
      
      logFile.close();
      
      Serial.println("  → Data logged to SD card");
      
      // Play log sound (only if no alert)
      if (buzzerWorking && !shouldAlert) {
        logSound();
      }
    } else {
      Serial.println("  ✗ Failed to open log file");
    }
  }
  
  // Wait before next reading
  delay(2000);
}

// ═══════════════════════════════════════════════════════════
// END OF CODE
// ═══════════════════════════════════════════════════════════
