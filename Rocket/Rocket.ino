#include "LoRaWan_APP.h"
#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <math.h>

// =====================
// LoRa
// =====================
#define RF_FREQUENCY                868000000
#define TX_OUTPUT_POWER             14
#define LORA_BANDWIDTH              0
#define LORA_SPREADING_FACTOR       7
#define LORA_CODINGRATE             1
#define LORA_PREAMBLE_LENGTH        8
#define LORA_SYMBOL_TIMEOUT         0
#define LORA_FIX_LENGTH_PAYLOAD_ON  false
#define LORA_IQ_INVERSION_ON        false

#define BUFFER_SIZE 220

// =====================
// I2C / Sensores
// =====================
#define SDA_PIN   43
#define SCL_PIN   44
#define MPU_ADDR  0x68   // si no va, prueba 0x69

// Registros MPU
#define REG_PWR_MGMT_1   0x6B
#define REG_ACCEL_XOUT_H 0x3B
#define REG_GYRO_XOUT_H  0x43
#define REG_ACCEL_CONFIG 0x1C
#define REG_GYRO_CONFIG  0x1B
#define REG_WHO_AM_I     0x75

TwoWire I2CBUS = TwoWire(0);
Adafruit_BME280 bme;

char txpacket[BUFFER_SIZE];
bool lora_idle = true;
static RadioEvents_t RadioEvents;
int txNumber = 0;

bool bmeOK = false;
bool mpuOK = false;

// Offsets gyro
float gx_offset = 0;
float gy_offset = 0;
float gz_offset = 0;

// =====================
// LoRa callback
// =====================
void OnTxDone(void) {
  Serial.println("TX done");
  lora_idle = true;
}

// =====================
// I2C scan
// =====================
void scanI2C() {
  Serial.println("Scanning I2C...");
  byte count = 0;

  for (byte addr = 1; addr < 127; addr++) {
    I2CBUS.beginTransmission(addr);
    byte error = I2CBUS.endTransmission();

    if (error == 0) {
      Serial.print("Find out in 0x");
      if (addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
      count++;
      delay(5);
    }
  }

  if (count == 0) {
    Serial.println("Don´t find I2C");
  } else {
    Serial.print("Total find out: ");
    Serial.println(count);
  }
  Serial.println("----------------------------------------");
}

// =====================
// Funciones MPU
// =====================
void writeByte(uint8_t reg, uint8_t data) {
  I2CBUS.beginTransmission(MPU_ADDR);
  I2CBUS.write(reg);
  I2CBUS.write(data);
  I2CBUS.endTransmission();
}

uint8_t readByte(uint8_t reg) {
  I2CBUS.beginTransmission(MPU_ADDR);
  I2CBUS.write(reg);
  I2CBUS.endTransmission(false);
  I2CBUS.requestFrom(MPU_ADDR, (uint8_t)1);

  if (I2CBUS.available()) return I2CBUS.read();
  return 0xFF;
}

int16_t readInt16(uint8_t reg) {
  I2CBUS.beginTransmission(MPU_ADDR);
  I2CBUS.write(reg);
  I2CBUS.endTransmission(false);
  I2CBUS.requestFrom(MPU_ADDR, (uint8_t)2);

  if (I2CBUS.available() < 2) return 0;
  return (I2CBUS.read() << 8) | I2CBUS.read();
}

void calibrateGyro() {
  Serial.println("Calibrating gyroscope... do not move the board");
  const int samples = 500;
  long gx_sum = 0, gy_sum = 0, gz_sum = 0;

  for (int i = 0; i < samples; i++) {
    gx_sum += readInt16(REG_GYRO_XOUT_H);
    gy_sum += readInt16(REG_GYRO_XOUT_H + 2);
    gz_sum += readInt16(REG_GYRO_XOUT_H + 4);
    delay(5);
  }

  gx_offset = gx_sum / (float)samples;
  gy_offset = gy_sum / (float)samples;
  gz_offset = gz_sum / (float)samples;

  Serial.println("Offsets gyro calculated");
  Serial.println("----------------------------------------");
}

bool initMPU() {
  uint8_t who = readByte(REG_WHO_AM_I);
  Serial.print("WHO_AM_I = 0x");
  Serial.println(who, HEX);

  writeByte(REG_PWR_MGMT_1, 0x00);
  delay(100);

  writeByte(REG_ACCEL_CONFIG, 0x00);
  delay(10);

  writeByte(REG_GYRO_CONFIG, 0x00);
  delay(10);

  int16_t ax = readInt16(REG_ACCEL_XOUT_H);
  int16_t ay = readInt16(REG_ACCEL_XOUT_H + 2);
  int16_t az = readInt16(REG_ACCEL_XOUT_H + 4);

  if (ax != 0 || ay != 0 || az != 0) {
    Serial.println("MPU initialized in compatible mode");
    calibrateGyro();
    return true;
  }

  Serial.println("MPU not detected");
  return false;
}

// =====================
// Setup
// =====================
void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Start sender");

  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);

  I2CBUS.begin(SDA_PIN, SCL_PIN);
  delay(300);

  scanI2C();

  if (bme.begin(0x77, &I2CBUS)) {
    Serial.println("BME280 OK in 0x77");
    bmeOK = true;
  } else if (bme.begin(0x76, &I2CBUS)) {
    Serial.println("BME280 OK in 0x76");
    bmeOK = true;
  } else {
    Serial.println("BME280 not detected");
    bmeOK = false;
  }

  mpuOK = initMPU();

  RadioEvents.TxDone = OnTxDone;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);

  Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                    LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                    LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                    true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

  Serial.println("LoRa sender ready");
  Serial.println("----------------------------------------");
}

// =====================
// Loop
// =====================
void loop() {
  if (lora_idle) {
    String payload = "ID:" + String(txNumber);

    float temp = 0, pres = 0, hum = 0, alt = 0;
    float ax_g = 0, ay_g = 0, az_g = 0;
    float gx_dps = 0, gy_dps = 0, gz_dps = 0;
    float a_total = 0;

    // ===== BME =====
    if (bmeOK) {
      temp = bme.readTemperature();
      pres = bme.readPressure() / 100.0F;
      hum  = bme.readHumidity();
      alt  = bme.readAltitude(1013.25);

      payload += ",T:" + String(temp, 2);
      payload += ",P:" + String(pres, 2);
      payload += ",H:" + String(hum, 2);
      payload += ",ALT:" + String(alt, 2);
    } else {
      payload += ",BME:ERR";
    }

    // ===== MPU =====
    if (mpuOK) {
      const int samples = 20;
      long ax_sum = 0, ay_sum = 0, az_sum = 0;
      long gx_sum = 0, gy_sum = 0, gz_sum = 0;

      for (int i = 0; i < samples; i++) {
        ax_sum += readInt16(REG_ACCEL_XOUT_H);
        ay_sum += readInt16(REG_ACCEL_XOUT_H + 2);
        az_sum += readInt16(REG_ACCEL_XOUT_H + 4);

        gx_sum += readInt16(REG_GYRO_XOUT_H);
        gy_sum += readInt16(REG_GYRO_XOUT_H + 2);
        gz_sum += readInt16(REG_GYRO_XOUT_H + 4);

        delay(5);
      }

      float ax_raw = ax_sum / (float)samples;
      float ay_raw = ay_sum / (float)samples;
      float az_raw = az_sum / (float)samples;

      float gx_raw = gx_sum / (float)samples - gx_offset;
      float gy_raw = gy_sum / (float)samples - gy_offset;
      float gz_raw = gz_sum / (float)samples - gz_offset;

      ax_g = ax_raw / 16384.0;
      ay_g = ay_raw / 16384.0;
      az_g = az_raw / 16384.0;

      gx_dps = gx_raw / 131.0;
      gy_dps = gy_raw / 131.0;
      gz_dps = gz_raw / 131.0;

      a_total = sqrt(ax_g * ax_g + ay_g * ay_g + az_g * az_g);

      payload += ",AX:" + String(ax_g, 3);
      payload += ",AY:" + String(ay_g, 3);
      payload += ",AZ:" + String(az_g, 3);
      payload += ",AT:" + String(a_total, 3);
      payload += ",GX:" + String(gx_dps, 3);
      payload += ",GY:" + String(gy_dps, 3);
      payload += ",GZ:" + String(gz_dps, 3);
    } else {
      payload += ",MPU:ERR";
    }

    payload.toCharArray(txpacket, BUFFER_SIZE);

    // ===== SALIDA SERIAL COMO QUIERES =====
    Serial.println("----------------------------------------");
    Serial.print("ID: ");
    Serial.println(txNumber);

    if (bmeOK) {
      Serial.print("BME | T: ");
      Serial.print(temp, 2);
      Serial.print(" C | P: ");
      Serial.print(pres, 2);
      Serial.print(" hPa | H: ");
      Serial.print(hum, 2);
      Serial.print(" % | ALT: ");
      Serial.print(alt, 2);
      Serial.println(" m");
    } else {
      Serial.println("BME | NOT CONNECTED");
    }

    if (mpuOK) {
      Serial.print("MPU | AX: ");
      Serial.print(ax_g, 3);
      Serial.print(" AY: ");
      Serial.print(ay_g, 3);
      Serial.print(" AZ: ");
      Serial.print(az_g, 3);
      Serial.print(" | AT: ");
      Serial.print(a_total, 3);
      Serial.print(" g | GX: ");
      Serial.print(gx_dps, 3);
      Serial.print(" GY: ");
      Serial.print(gy_dps, 3);
      Serial.print(" GZ: ");
      Serial.println(gz_dps, 3);
    } else {
      Serial.println("MPU | NOT CONNECTED");
    }

    Radio.Send((uint8_t *)txpacket, strlen(txpacket));
    lora_idle = false;

    txNumber++;
    delay(2000);
  }

  Radio.IrqProcess();
}