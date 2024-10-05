#include <SPI.h>
#include <RF24.h>

#define CE_PIN 18
#define CSN_PIN 23

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);  // Set power level to low
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char receivedMessage[32] = {0};
    radio.read(receivedMessage, sizeof(receivedMessage));
    Serial.print("Received Message: ");
    Serial.println(receivedMessage);
  }

  delay(1000);
}
