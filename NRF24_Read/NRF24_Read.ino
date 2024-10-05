#include <RF24.h>
RF24 radio(4, 5);

#define ledPin 2
#define echoPin 12
#define trigPin 13
#define ioPin 14
#define redPin 33
#define greenPin 32

long duration, distance;
uint8_t receivedMessage;
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ioPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);

  //Receiver
  radio.begin();
  radio.setChannel(90);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(0, address);
  radio.startListening();

}

void loop() {
  uint8_t receivedNumber = 0;
  if (radio.available()) {
    radio.read(&receivedNumber, sizeof(receivedNumber));
    Serial.println(receivedNumber);
    if (receivedNumber == 123) {
      Serial.println("RECEIVED");
      //Ultrasonic
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
    
      duration = pulseIn(echoPin, HIGH);
      distance = duration / 58.2;
    
      //LED
      if (distance <= 10) {
        digitalWrite(ioPin, LOW);
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        Serial.println("ON");
      }
      else {
        digitalWrite(ioPin, HIGH);
        digitalWrite(greenPin, LOW);
        digitalWrite(redPin, HIGH);
        Serial.println("OFF");
      }
    }
  }
  else {
      Serial.println("NOT RECEIVED");
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
    }
  delay(500);
}
