#include "Arduino.h"

#define GPS_RX    34   // GNSS_RX
#define GPS_TX    33   // GNSS_TX
#define GPS_RST   35   // GNSS_RST
#define VEXT_CTRL 3    // Vext control

unsigned long countBytes = 0;
unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("=== TEST GPS GNSS ===");

  // Encender Vext (en Heltec suele ser activo en LOW)
  pinMode(VEXT_CTRL, OUTPUT);
  digitalWrite(VEXT_CTRL, LOW);
  delay(200);

  // Sacar el GPS de reset
  pinMode(GPS_RST, OUTPUT);
  digitalWrite(GPS_RST, LOW);
  delay(50);
  digitalWrite(GPS_RST, HIGH);
  delay(500);

  Serial1.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial.println("Esperando datos...");
}

void loop() {
  while (Serial1.available()) {
    char c = Serial1.read();
    countBytes++;
    Serial.write(c);
  }

  if (millis() - lastPrint > 2000) {
    lastPrint = millis();
    Serial.println();
    Serial.print("Bytes recibidos: ");
    Serial.println(countBytes);
    Serial.println("----------------------------------------");
  }
}
