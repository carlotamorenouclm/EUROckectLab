#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SDA_PIN D2   // GPIO4
#define SCL_PIN D1   // GPIO5

Adafruit_BME280 bme;

void scanI2C() {
  Serial.println("Escaneando I2C...");
  byte count = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Dispositivo encontrado en 0x");
      Serial.println(address, HEX);
      count++;
      delay(5);
    }
  }

  if (count == 0) {
    Serial.println("❌ No se detecta nada en I2C");
  } else {
    Serial.println("✅ Escaneo completado");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== TEST BME280 + ESP8266 ===");

  // Inicializar I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Escanear dispositivos
  scanI2C();

  // Intentar iniciar sensor (direcciones típicas)
  bool status = false;

  if (bme.begin(0x76)) {
    Serial.println("✅ BME280 detectado en 0x76");
    status = true;
  } 
  else if (bme.begin(0x77)) {
    Serial.println("✅ BME280 detectado en 0x77");
    status = true;
  }

  if (!status) {
    Serial.println("❌ No se detecta BME280");
    Serial.println("Revisa:");
    Serial.println("- Cableado (D1=SCL, D2=SDA)");
    Serial.println("- Alimentación (3.3V)");
    Serial.println("- Si es BMP280 en vez de BME280");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("\nSistema listo 🚀\n");
}

void loop() {
  Serial.println("----- LECTURA -----");

  float temp = bme.readTemperature();
  float pres = bme.readPressure() / 100.0F;
  float hum  = bme.readHumidity();
  float alt  = bme.readAltitude(1013.25);

  if (isnan(temp) || isnan(pres) || isnan(hum)) {
    Serial.println("❌ Error leyendo sensor");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println(" °C");

    Serial.print("Presion: ");
    Serial.print(pres);
    Serial.println(" hPa");

    Serial.print("Humedad: ");
    Serial.print(hum);
    Serial.println(" %");

    Serial.print("Altitud aprox: ");
    Serial.print(alt);
    Serial.println(" m");
  }

  Serial.println();
  delay(2000);
}