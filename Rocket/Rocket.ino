#include "LoRaWan_APP.h"
#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define RF_FREQUENCY                868000000
#define TX_OUTPUT_POWER             14
#define LORA_BANDWIDTH              0
#define LORA_SPREADING_FACTOR       7
#define LORA_CODINGRATE             1
#define LORA_PREAMBLE_LENGTH        8
#define LORA_SYMBOL_TIMEOUT         0
#define LORA_FIX_LENGTH_PAYLOAD_ON  false
#define LORA_IQ_INVERSION_ON        false

#define BUFFER_SIZE 128

TwoWire I2CBME = TwoWire(0);
Adafruit_BME280 bme;

char txpacket[BUFFER_SIZE];
bool lora_idle = true;
static RadioEvents_t RadioEvents;
int txNumber = 0;

void OnTxDone(void)
{
  Serial.println("TX done");
  lora_idle = true;
}

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Inicio sender");

  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);

  I2CBME.begin(43, 44);

  if (!bme.begin(0x77, &I2CBME)) {
    Serial.println("BME280 no detectado");
    while (1) {
      Serial.println("esperando sensor...");
      delay(1000);
    }
  }
  Serial.println("BME280 OK");

  RadioEvents.TxDone = OnTxDone;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);

  Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                    LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                    LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                    true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

  Serial.println("LoRa sender listo");
}

void loop() {
  if (lora_idle) {
    float temp = bme.readTemperature();
    float pres = bme.readPressure() / 100.0F;
    float hum  = bme.readHumidity();
    float alt  = bme.readAltitude(1013.25);

    snprintf(txpacket, BUFFER_SIZE,
             "ID:%d,T:%.2f,P:%.2f,H:%.2f,A:%.2f",
             txNumber++, temp, pres, hum, alt);

    Serial.print("Enviando: ");
    Serial.println(txpacket);

    Radio.Send((uint8_t *)txpacket, strlen(txpacket));
    lora_idle = false;

    delay(2000);
  }

  Radio.IrqProcess();
}
