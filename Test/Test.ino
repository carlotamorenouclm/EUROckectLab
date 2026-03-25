/*
  CELESTIAL HORIZONS - TEST 1
  Scanner I2C pour verifier le branchement du BME280
*/

#include <Wire.h>

// Broches de la Heltec V4
#define SDA_PIN 17
#define SCL_PIN 18

void setup() {
  Serial.begin(115200);
  delay(2000); // Laisse le temps d'ouvrir le moniteur série

  Serial.println("\n--- CELESTIAL HORIZONS ---");
  Serial.println("Initialisation du Radar I2C sur les broches 17(SDA) et 18(SCL)...");

  Wire.begin(SDA_PIN, SCL_PIN);
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scan du bus I2C en cours...");

  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("SUCCESS : Capteur trouve a l'adresse hexadecimale 0x");
      if (address < 16) { Serial.print("0"); }
      Serial.print(address, HEX);

      // Verification specifique pour le BME280
      if (address == 0x76 || address == 0x77) {
        Serial.println("  >>> BINGO ! C'est ton BME280 ! Le cablage est parfait !");
      } else if (address == 0x3C) {
        Serial.println("  (C'est l'ecran de la Heltec, c'est normal)");
      } else {
        Serial.println("  (Composant inconnu)");
      }
      nDevices++;
    }
  }

  if (nDevices == 0) {
    Serial.println("ERREUR : Rien trouve. Verifie tes 4 fils (3V3, GND, Bleu sur 17, Vert sur 18)");
  } else {
    Serial.println("Scan termine.\n");
  }

  delay(5000);
}