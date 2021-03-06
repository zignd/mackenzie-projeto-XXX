#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ArduinoJson.h>
#include <printf.h>

// Joystick
const int JOY_PIN1 = A4;
const int JOY_PIN2 = A5;

// Directions
const int DIR_NONE = -1;
const int DIR_FORWARD = 1;
const int DIR_BACKWARD = 2;
const int DIR_RIGHT = 3;
const int DIR_LEFT = 4;

// nRF24L01+
const int NRF_CE = 7;
const int NRF_CSN = 8;
RF24 radio(NRF_CE, NRF_CSN);
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  radio.openWritingPipe(address);

  Serial.begin(9600);
  printf_begin();
}

void loop() {
  // For debugging
  // radio.printDetails();
  int direction = getDirection();
  Serial.print("Direction: ");
  Serial.println(direction);

  char text[2];
  sprintf(text, "%d", direction);
  Serial.print("Sent: ");
  Serial.println(text);
  Serial.println(radio.write(&text, sizeof(text)));
}

int getDirection() {
  int x = readJoy(JOY_PIN1);
  int y = readJoy(JOY_PIN2);

  if (isTowardMin(y) && isTowardMin(x)) {
    if (y <= x) {
      return DIR_FORWARD;
    } else {
      return DIR_LEFT;
    }
  } else if (isTowardMin(y) && isTowardMax(x)) {
    int invertY = 180-y;
    if (invertY >= x) {
      return DIR_FORWARD;
    } else {
      return DIR_RIGHT;
    }
  } else if (isTowardMax(y) && isTowardMax(x)) {
    if (y >= x) {
      return DIR_BACKWARD;
    } else {
      return DIR_RIGHT;
    }
  } else if (isTowardMax(y) && isTowardMin(x)) {
    int invertX = 180-x;
    if (y >= invertX) {
      return DIR_BACKWARD;
    } else {
      return DIR_LEFT;
    }
  } else if (isTowardMin(y)) {
    return DIR_FORWARD;
  } else if (isTowardMax(y)) {
    return DIR_BACKWARD;
  } else if (isTowardMin(x)) {
    return DIR_LEFT;
  } else if (isTowardMax(x)) {
    return DIR_RIGHT;
  } else {
    return DIR_NONE;
  }
}

int readJoy(int pin) {
  return map(analogRead(pin), 0, 1023, 1, 180);
}

bool isNeutral(int pos) {
  return pos >= 85 && pos <= 95;
}

bool isTowardMin(int pos) {
  return !isNeutral(pos) && pos < 85;
}

bool isTowardMax(int pos) {
  return !isNeutral(pos) && pos > 95;
}
