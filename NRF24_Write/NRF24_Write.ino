#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(15, 2);

long weight;

void setup() {
  radio.begin();
  radio.setChannel(90);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(0x1234567890LL);
}

void loop() {
  weight = 1;
  radio.write(&weight, sizeof(weight));
  delay(1000);
}
