🚀 Celestial Horizons – EU Rocket Lab

📌 Overview

This project is part of the EU🚀ROCKET LAB – BIP 2026 program.
Our mission is to design and build an onboard instrumentation system for an experimental rocket capable of:
	•	Measuring flight data (acceleration, altitude, temperature, GPS)
	•	Storing high-frequency data locally
	•	Transmitting essential data via LoRa communication

The system is optimized for extreme conditions such as high acceleration, vibrations, and limited space.  ￼

⸻

🧠 System Architecture

🔧 Core Components
	•	ESP32 Heltec WiFi LoRa V2/V4 – Main microcontroller
	•	LiPo Battery (3.7V, 800mAh) – Power supply
	•	IMU (LSM6DSOX / MPU-6050) – Acceleration & rotation
	•	Barometer (BMP388 / BME280) – Altitude & temperature
	•	GPS (NEO-6M) – Position tracking
	•	Micro SD Module (SPI) – Data storage

🔌 Communication Buses
	•	I2C → Sensors (IMU + Barometer)
	•	SPI → SD Card (high-speed logging)

This architecture minimizes wiring and improves reliability under vibration.  ￼

⸻

🚀 Flight Phases (Finite State Machine)

The software is based on a Finite State Machine (FSM):
	1.	IDLE – Low power mode before launch
	2.	BOOST – High-frequency acquisition (200 Hz)
	3.	FLIGHT – Altitude tracking & stability
	4.	DESCENT – Parachute tracking + GPS activation
	5.	LANDING – Data transmission via LoRa

⸻

📡 Data Transmission Strategy

During Flight (Minimalist Mode)
	•	Beacon every 10 seconds
	•	Data sent:
	•	Altitude
	•	Timestamp
	•	Battery level

👉 High-frequency data is stored locally (SD card) to avoid LoRa overload.  ￼

After Landing

Two-step transmission:
	1.	Emergency Packet
	•	GPS coordinates
	•	Maximum altitude
	•	Peak acceleration
	2.	Full Data Dump
	•	Complete flight history
	•	Pressure, temperature, IMU data

⸻

🔋 Energy Management

To optimize battery life:
	•	Use of Light Sleep / Deep Sleep modes
	•	Sensors activated only when needed
	•	LoRa transmission only after landing
	•	Adaptive sampling frequency depending on flight phase  ￼

⸻

💻 Software Structure

Initialization (setup())
	•	initI2C() → Sensors setup
	•	initSPI_SD() → SD card initialization
	•	initLoRa() → Radio configuration

Main Loop (loop())
	•	Handles state transitions
	•	Prioritizes:
	•	Data acquisition (BOOST phase)
	•	Storage (SPI)
	•	Transmission (after landing)

⸻

📂 Project Structure

/src
  ├── main.ino
  ├── sensors/
  ├── communication/
  ├── storage/

/docs
  ├── wiring_diagram.png
  ├── presentation.pdf

/data
  ├── flight_log.csv


⸻

⚠️ Constraints & Challenges
	•	High acceleration during launch
	•	Strong vibrations
	•	Limited space inside rocket
	•	Energy constraints
	•	LoRa bandwidth limitations

⸻

🛠️ Future Improvements
	•	Data compression before transmission
	•	Error correction (CRC + retransmission)
	•	Real-time ground station visualization
	•	Improved GPS acquisition speed

⸻

👨‍🚀 Team

Celestial Horizons – Group 5
	•	Sophie Adenot
	•	Raphaël Liégeois
	•	Pablo Álvarez Fernández

⸻

📄 License

This project is developed for EU Rocket Lab (educational purpose).
