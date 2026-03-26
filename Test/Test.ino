// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BME280.h>
// #include <MPU9250_WE.h>
// #include <TinyGPS++.h>

// // GPs module pins
// #define GPS_RX 38
// #define GPS_TX 39
// #define VGNSS_CTRL 36


// TwoWire I2CBus = TwoWire(0);

// Adafruit_BME280 bme;
// MPU9250_WE mpu = MPU9250_WE(&I2CBus, 0x68);
// TinyGPSPlus gps;

// unsigned long lastPrintTime = 0;

// void setup() {
//   Serial.begin(115200);
//   delay(3000);
//   Serial.println("Starting");
  
//   // init gps
//   pinMode(VGNSS_CTRL, OUTPUT);
//   digitalWrite(VGNSS_CTRL, LOW); // Pulling LOW turns the GNSS power ON
//   delay(500); // Give the GPS a moment to wake up

//   Serial1.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
//   Serial.println("GPS Connector Powered and Serial Initialized.");

//   //init BME280
//   I2CBus.begin(43, 44);

//   if (!bme.begin(0x77, &I2CBus)) {
//     Serial.println("BME280 not detected.");
//     while (1) {
//       Serial.println("Waiting...");
//       delay(1000);
//     }
//   }

//   Serial.println("BME280 detected");

//   // init MPU9250

//   if (!mpu.init()) {
//     Serial.println("MPU9250 Accel/Gyro not detected.");
//   } else {
//     Serial.println("MPU9250 Accel/Gyro detected.");
//   }
//   // The MPU-9250 has a separate initialization for the Magnetometer
//   if (!mpu.initMagnetometer()) {
//     Serial.println("MPU9250 Magnetometer not detected.");
//   } else {
//     Serial.println("MPU9250 Magnetometer detected");
//   }

//   mpu.autoOffsets();
//   mpu.setGyrRange(MPU9250_GYRO_RANGE_250);
//   mpu.setAccRange(MPU9250_ACC_RANGE_2G);
  
//   Serial.println("Sensors initialized");
// }

// void loop() {
//   // CRITICAL: Keep reading GPS data as fast as possible in every loop iteration
//   while (Serial1.available() > 0) {
//     gps.encode(Serial1.read());
//   }

//   // Only print data every 2 seconds (Non-blocking)
//   if (millis() - lastPrintTime > 2000) {
//     lastPrintTime = millis();
    
//     Serial.println("----------------------------------------");
    
//     // --- BME280 ---
//     Serial.print("BME280 | Temp: "); Serial.print(bme.readTemperature());
//     Serial.print(" C | Hum: "); Serial.print(bme.readHumidity());
//     Serial.println(" %");
//     Serial.print("Altitude (m): "); Serial.println(bme.readAltitude(375));

//     // --- MPU9250 ---
//     xyzFloat acc = mpu.getGValues();
//     xyzFloat mag = mpu.getMagValues();
//     Serial.print("MPU9250| Accel Z: "); Serial.print(acc.z);
//     Serial.print(" | Mag X: "); Serial.print(mag.x);
//     Serial.print(" Y: "); Serial.print(mag.y);
//     Serial.print(" Z: "); Serial.println(mag.z);

//     // --- GPS ---
//     Serial.print("GPS    | Sats: "); Serial.print(gps.satellites.value());
//     if (gps.location.isValid()) {
//       Serial.print(" | Lat: "); Serial.print(gps.location.lat(), 6);
//       Serial.print(" | Lng: "); Serial.println(gps.location.lng(), 6);
//     } else {
//       Serial.println(" | Searching for satellites...");
//     }
//   }
// }


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MPU9250_WE.h>
#include <TinyGPS++.h>

// ===== POWER & I2C SETUP =====
#define VEXT_CTRL       36      // FIXED: Correct V4 board pin for GNSS power
#define I2C_SDA         43
#define I2C_SCL         44
#define GPS_RX          38
#define GPS_TX          39
#define GPS_BAUD        9600
#define I2C_FREQ        100000  // FIXED: Stable speed for shared bus

TwoWire I2CBus(0);
Adafruit_BME280 bme;
MPU9250_WE* mpu = nullptr;
TinyGPSPlus gps;

bool bmeOK = false;
bool mpuOK = false;
bool magOK = false;

unsigned long lastPrintTime = 0;

void i2cScan() {
  Serial.println("I2C Scan...");
  uint8_t count = 0;
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found @ 0x");
      if (addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
      count++;
    }
  }
  Serial.print("Total devices detected: ");
  Serial.println(count);
  Serial.println("");
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("=== STARTING FULL SYSTEM ===");

  // ---------- 1. Enable External Power Rails ----------
  pinMode(VEXT_CTRL, OUTPUT);
  digitalWrite(VEXT_CTRL, LOW);  // Active LOW enables Ve output
  delay(300);                    // Give GPS & peripherals time to boot
  Serial.println("Vext power enabled on GPIO36.");

  // ---------- 2. Initialize GPS UART ----------
  Serial1.begin(GPS_BAUD, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial1.setRxBufferSize(2048);
  Serial.println("GPS UART initialized (RX=38 TX=39 @9600).");

  // ---------- 3. Initialize I2C Bus (Shared) ----------
  I2CBus.begin(I2C_SDA, I2C_SCL, I2C_FREQ);
  
  // Scan to confirm device presence BEFORE initializing libraries
  i2cScan();

  // ---------- 4. Initialize BME280 ----------
  Serial.println("Initializing BME280...");
  if (!bme.begin(0x77, &I2CBus)) {
    Serial.println("BME not found at 0x77, trying 0x76...");
    if (!bme.begin(0x76, &I2CBus)) {
      Serial.println("ERROR: BME280 NOT DETECTED!");
      bmeOK = false;
    } else {
      Serial.println("BME280 OK @0x76");
      bmeOK = true;
    }
  } else {
    Serial.println("BME280 OK @0x77");
    bmeOK = true;
  }

  // ---------- 5. Initialize MPU9250 ----------
  Serial.println("Initializing MPU9250...");
  
  // First try 0x68
  mpu = new MPU9250_WE(&I2CBus, 0x68);
  if (!mpu->init()) {
    Serial.println("MPU not found at 0x68, trying 0x69...");
    delete mpu;
    
    // Second try 0x69
    mpu = new MPU9250_WE(&I2CBus, 0x69);
    if (!mpu->init()) {
      Serial.println("ERROR: MPU9250 NOT DETECTED!");
      delete mpu;
      mpu = nullptr;
      mpuOK = false;
    } else {
      Serial.println("MPU9250 OK @0x69");
      mpuOK = true;
    }
  } else {
    Serial.println("MPU9250 OK @0x68");
    mpuOK = true;
  }

  if (mpuOK && mpu != nullptr) {
    // Configure ranges
    mpu->setGyrRange(MPU9250_GYRO_RANGE_250);
    mpu->setAccRange(MPU9250_ACC_RANGE_2G);
    
    // Check Magnetometer
    Serial.println("Checking Magnetometer...");
    if (mpu->initMagnetometer()) {
      Serial.println("Magnetometer OK");
      magOK = true;
    } else {
      Serial.println("WARNING: Magnetometer NOT detected (common with fake/MPU6050 boards)");
      magOK = false;
    }

    // Take auto-offsets (keep board still!)
    Serial.println("Taking auto-offsets (keep board stationary)...");
    delay(2000);
    mpu->autoOffsets();
  }

  Serial.println("========================================");
  Serial.println("SYSTEM INIT COMPLETE");
  Serial.println("========================================");
}

void loop() {
  // Feed GPS continuously
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
  }

  // Print data every 2 seconds
  if (millis() - lastPrintTime >= 2000) {
    lastPrintTime = millis();

    Serial.println("----------------------------------------");

    // ----- BME280 Data -----
    Serial.print("BME280 |");
    if (bmeOK) {
      Serial.print(" Temp: "); Serial.print(bme.readTemperature(), 1);
      Serial.print("°C | Hum: "); Serial.print(bme.readHumidity(), 1);
      Serial.print("% | Pres: "); Serial.print(bme.readPressure() / 100.0f, 1);
      Serial.print("hPa | Alt: "); Serial.print(bme.readAltitude(1013.25), 1);
      Serial.println("m");
    } else {
      Serial.println(" NOT CONNECTED");
    }

    // ----- MPU9250 Data -----
    Serial.print("MPU9250|");
    if (mpuOK && mpu != nullptr) {
      xyzFloat acc = mpu->getGValues();
      xyzFloat mag = mpu->getMagValues();
      
      Serial.print(" AccX:"); Serial.print(acc.x, 3);
      Serial.print(" Y:"); Serial.print(acc.y, 3);
      Serial.print(" Z:"); Serial.print(acc.z, 3);
      Serial.print("g | MagX:"); Serial.print(mag.x, 1);
      Serial.print(" Y:"); Serial.print(mag.y, 1);
      Serial.print(" Z:"); Serial.print(mag.z, 1);
      Serial.println("µT");
      
      if (!magOK) {
        Serial.println("NOTE: Magnetometer unavailable (fake/MPU6050 chip?)");
      }
    } else {
      Serial.println(" NOT CONNECTED");
    }

    // ----- GPS Data -----
    Serial.print("GPS    | Sats: "); Serial.print(gps.satellites.value());
    if (gps.location.isValid()) {
      Serial.print(" | Lat: "); Serial.print(gps.location.lat(), 6);
      Serial.print(" Lon: "); Serial.print(gps.location.lng(), 6);
    } else {
      Serial.print(" | NO FIX");
    }
    Serial.println();

    // Watchdog for GPS
    static unsigned long lastGPSByte = 0;
    if (Serial1.available() > 0) {
      lastGPSByte = millis();
    }
    if (lastGPSByte > 0 && millis() - lastGPSByte > 5000) {
      Serial.println("WARNING: No GPS data received for 5+ seconds");
    }
  }
}
