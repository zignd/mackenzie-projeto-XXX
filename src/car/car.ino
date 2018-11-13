#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Bridge
const int BDG_IN1 = 3;
const int BDG_IN2 = 4;
const int BDG_IN3 = 5;
const int BDG_IN4 = 6;

// nRF24L01+
const int NRF_CE = 7;
const int NRF_CSN = 8;

RF24 radio(NRF_CE, NRF_CSN);

const byte address[6] = "00001";

void setup() {
  pinMode(BDG_IN1, OUTPUT);
  pinMode(BDG_IN2, OUTPUT);
  pinMode(BDG_IN3, OUTPUT);
  pinMode(BDG_IN4, OUTPUT);

  Serial.begin(9600);
  
  radio.begin();
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    Serial.println("available");
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(text);
  } else {
    Serial.println("not available");
  }

  delay(1000);
  
//  testMotors();
}

void testMotors() {
//  moveForward();
//  delay(2000);
//  
//  stopMotors();
//  delay(500);
  
//  moveBackward();
//  delay(2000);
//  
//  stopMotors();
//  delay(500);

//  turnRight();
//  delay(2000);
//
//  stopMotors();
//  delay(500);

  turnLeft();
  delay(2000);

  stopMotors();
  delay(500);
}

void moveForward() {
  digitalWrite(BDG_IN1, HIGH);
  digitalWrite(BDG_IN2, LOW);

  digitalWrite(BDG_IN3, HIGH);
  digitalWrite(BDG_IN4, LOW);
}

void moveBackward() {
  digitalWrite(BDG_IN1, LOW);
  digitalWrite(BDG_IN2, HIGH);

  digitalWrite(BDG_IN3, LOW);
  digitalWrite(BDG_IN4, HIGH);
}

void turnRight() {
  digitalWrite(BDG_IN1, HIGH);
  digitalWrite(BDG_IN2, LOW);

  digitalWrite(BDG_IN3, LOW);
  digitalWrite(BDG_IN4, HIGH);
}

void turnLeft() {
  digitalWrite(BDG_IN1, LOW);
  digitalWrite(BDG_IN2, HIGH);

  digitalWrite(BDG_IN3, HIGH);
  digitalWrite(BDG_IN4, LOW);
}

void stopMotors() {
  digitalWrite(BDG_IN1, HIGH);
  digitalWrite(BDG_IN2, HIGH);

  digitalWrite(BDG_IN3, HIGH);
  digitalWrite(BDG_IN4, HIGH);
}
