#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>
#include <printf.h>

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
  printf_begin();
  
  radio.begin();
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  // For debugging
  // radio.printDetails();
  if (radio.available()) {
    Serial.println("Radio available");
    char direction[2];
    radio.read(&direction, sizeof(direction));
    Serial.print("Direction received: ");
    Serial.println(direction);
    if (strcmp(direction, "1") == 0) {
      Serial.println("Moving forward");
      moveForward();
    } else if (strcmp(direction, "2") == 0) {
      Serial.println("Moving backward");
      moveBackward();
    } else if (strcmp(direction, "3") == 0) {
      Serial.println("Turning right");
      turnRight();
    } else if (strcmp(direction, "4") == 0) {
      Serial.println("Turning left");
      turnLeft();
    } else {
      Serial.println("Stopping motors");
      stopMotors();
    }
  } else {
    Serial.println("Radio not available");
  }
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
