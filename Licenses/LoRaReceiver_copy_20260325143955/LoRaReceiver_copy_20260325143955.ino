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

#define BUFFER_SIZE 64

char rxpacket[BUFFER_SIZE];
static RadioEvents_t RadioEvents;

bool lora_idle = true;
int16_t packetRssi = 0;
int16_t rxSize = 0;

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("setup");

  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);
  Serial.println("mcu ok");

  RadioEvents.RxDone = OnRxDone;
  Radio.Init(&RadioEvents);
  Serial.println("radio init ok");

  Radio.SetChannel(RF_FREQUENCY);
  Serial.println("channel ok");

  Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                    LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                    LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                    0, true, 0, 0, LORA_IQ_INVERSION_ON, true);
  Serial.println("rx config ok");
}

void loop() {
  if (lora_idle) {
    Serial.println("into RX mode");
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

  Serial.printf("received: %s | RSSI: %d | size: %d\n", rxpacket, packetRssi, rxSize);

  lora_idle = true;
}