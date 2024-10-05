#include <SPI.h>
#include <RF24.h>

#define CE_PIN D4
#define CSN_PIN D3

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(90);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);  // Set power level to low
  radio.stopListening();
}

void loop() {
  uint8_t numberToSend = 123; // Change this number as needed
  radio.write(&numberToSend, sizeof(numberToSend));
  Serial.print("Number Sent: ");
  Serial.println(numberToSend);
  delay(200);
}
