# 🚀 EU Rocket Lab - Celestial Horizons

## 📌 Overview
This project is part of the **EU Rocket Lab – BIP 2026** program.  
Our goal is to design and build an onboard electronic system for an experimental rocket.

The system collects flight data (acceleration, altitude, temperature, GPS) and transmits it via LoRa after landing.

---

## 🎯 Objectives
- Measure flight data in real-time
- Store high-frequency data locally
- Transmit key information via LoRa
- Ensure system reliability under extreme conditions

---

## 🧠 System Architecture

### 🔹 Main Board
- ESP32 Heltec WiFi LoRa V2 / V4
- Powered by LiPo battery (3.7V)

### 🔹 Sensors
- IMU (LSM6DSOX / MPU6050) → Acceleration & rotation
- Barometer (BMP388 / BME280) → Altitude & temperature
- GPS (NEO-6M) → Position tracking

### 🔹 Communication
- LoRa (low bandwidth, long range)

---

## ⚙️ Flight Phases

1. IDLE – Waiting on launch pad (low power mode)  
2. BOOST – High acceleration, high-frequency sampling  
3. FLIGHT – Altitude and stability tracking  
4. DESCENT – Parachute tracking  
5. LANDING – GPS + LoRa transmission  

---

## 📡 Data Transmission Strategy

### During Flight
- Send beacon every 10 seconds:
  - Altitude
  - Timestamp
  - Battery status
- High-frequency data is stored locally (SD card)

### After Landing
1. Emergency packet
   - GPS coordinates
   - Maximum altitude  

2. Full data dump
   - Acceleration (XYZ)
   - Pressure & temperature
   - Flight history  

---

## 🔌 Hardware Connections

### I2C Bus (Sensors)
- SDA / SCL shared between sensors  
- Used for:
  - IMU  
  - Barometer  

### SPI Bus (SD Card)
- High-speed data logging  
- Required for 100–200 Hz sampling  

---

## 🔋 Energy Management
- LiPo battery (800mAh)  
- Low power modes (light sleep / deep sleep)  
- Sensors activated depending on flight phase  
- LoRa enabled only after landing  

---

## 🧪 Ground Station
- ESP32 LoRa receiver  
- Serial monitor for data visualization  

Optional:
- Real-time graphs  
- GPS map display  

---

## ⚠️ Challenges
- High acceleration & vibrations  
- Limited space  
- Power constraints  
- Data transmission limits  

---

## 📂 Project Structure (example)

```

/code
main.ino
sensors.cpp
lora.cpp

/hardware
wiring_diagram.png

/data
flight_logs.csv

```

---

## 👥 Team
Celestial Horizons (Group 5)

- Sophie Adenot  
- Raphaël Liégeois  
- Pablo Álvarez Fernández  

---

## 🚀 Future Improvements
- Better data compression  
- Improved GPS accuracy  
- Real-time visualization dashboard  
- Enhanced power optimization  

