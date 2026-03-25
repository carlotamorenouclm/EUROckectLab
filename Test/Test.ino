#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

TwoWire I2CBME = TwoWire(0);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Début");

  I2CBME.begin(43, 44);

  if (!bme.begin(0x77, &I2CBME)) {
    Serial.println("BME280 non detecte");
    while (1) {
      Serial.println("attente...");
      delay(1000);
    }
  }

  Serial.println("BME280 detecte");
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(bme.readTemperature());
  Serial.print(" C | Pression: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.print(" hPa | Humidite: ");
  Serial.print(bme.readHumidity());
  Serial.print(" % | Altitude: ");
  Serial.println(bme.readAltitude(1013.25));

  delay(2000);
}