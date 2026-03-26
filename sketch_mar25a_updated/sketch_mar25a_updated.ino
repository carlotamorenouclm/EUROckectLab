#include "LoRaWan_APP.h"
#include "Arduino.h"

#define RF_FREQUENCY                868000000
#define LORA_BANDWIDTH              0
#define LORA_SPREADING_FACTOR       7
#define LORA_CODINGRATE             1
#define LORA_PREAMBLE_LENGTH        8
#define LORA_SYMBOL_TIMEOUT         0
#define LORA_FIX_LENGTH_PAYLOAD_ON  false
#define LORA_IQ_INVERSION_ON        false

#define BUFFER_SIZE 220

char rxpacket[BUFFER_SIZE];
static RadioEvents_t RadioEvents;

bool lora_idle = true;
int16_t packetRssi = 0;
int16_t rxSize = 0;

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void printParsedData(char *data);
void printField(const char *data, const char *key, const char *label, const char *unit = "");

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Start receiver");

  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);

  RadioEvents.RxDone = OnRxDone;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);

  Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                    LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                    LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                    0, true, 0, 0, LORA_IQ_INVERSION_ON, false);

  Serial.println("Receiver ready");
}

void loop() {
  if (lora_idle) {
    Serial.println("Waiting...");
    lora_idle = false;
    Radio.Rx(0);
  }

  Radio.IrqProcess();
  delay(200);
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
  packetRssi = rssi;
  rxSize = size;

  if (size >= BUFFER_SIZE) size = BUFFER_SIZE - 1;

  memcpy(rxpacket, payload, size);
  rxpacket[size] = '\0';

  Serial.println("\n========================================");
  Serial.printf("📥 Message received | RSSI: %d | SNR: %d | size: %d\n", packetRssi, snr, rxSize);
  Serial.print("RAW: ");
  Serial.println(rxpacket);

  printParsedData(rxpacket);
  Serial.println("========================================\n");

  lora_idle = true;
}

void printParsedData(char *data) {
  Serial.println("Decoded data:");

  printField(data, "ID:",  "ID");
  printField(data, "T:",   "Temperature", " C");
  printField(data, "P:",   "Pressure", " hPa");
  printField(data, "H:",   "Humidity", " %");
  printField(data, "ALT:", "Altitude", " m");

  printField(data, "AX:", "AX", " g");
  printField(data, "AY:", "AY", " g");
  printField(data, "AZ:", "AZ", " g");
  printField(data, "AT:", "A total", " g");

  printField(data, "GX:", "GX", " dps");
  printField(data, "GY:", "GY", " dps");
  printField(data, "GZ:", "GZ", " dps");

  if (strstr(data, "BME:ERR")) {
    Serial.println("BME: ERROR");
  }

  if (strstr(data, "MPU:ERR")) {
    Serial.println("MPU: ERROR");
  }
}

void printField(const char *data, const char *key, const char *label, const char *unit) {
  const char *start = strstr(data, key);
  if (!start) return;

  start += strlen(key);
  const char *end = strchr(start, ',');

  char value[24];
  size_t len = end ? (size_t)(end - start) : strlen(start);
  if (len >= sizeof(value)) len = sizeof(value) - 1;

  strncpy(value, start, len);
  value[len] = '\0';

  Serial.print(label);
  Serial.print(": ");
  Serial.print(value);
  Serial.println(unit);
}
