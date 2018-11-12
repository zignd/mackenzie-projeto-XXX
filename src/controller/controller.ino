#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ArduinoJson.h>

// Joystick
const int JOY_PIN1 = A0;
const int JOY_PIN2 = A1;

// Directions
const int DIR_NONE = -1;
const int DIR_FORWARD = 1;
const int DIR_BACKWARD = 2;
const int DIR_RIGHT = 3;
const int DIR_LEFT = 4;

// nRF24L01+
const int NRF_CE = 5;
const int NRF_CSN = 6;
RF24 radio(NRF_CE, NRF_CSN);
const byte address[4] = "1";

void setup() {
  //const int JOY_PIN3 = 7;
  //int JOY_SW;
  //JOY_SW = digitalRead(JOY_PIN3);
  //pinMode(JOY_PIN3, INPUT_PULLUP);

  radio.begin();
  radio.stopListening();
  radio.setAddressWidth(4);
  //radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(address);

  Serial.begin(9600);
}

void loop() {
//  int direction = getDirection();
//  Serial.println(direction);
//
//  const size_t msgBufferSize = JSON_OBJECT_SIZE(1);
//  StaticJsonBuffer<msgBufferSize> jsonBuffer;
//  JsonObject& root = jsonBuffer.createObject();
//  root["direction"] = direction;

  const char text[] = "ayy lmao";
  Serial.println(radio.write(&text, sizeof(text)));
  //radio.write(&root, sizeof(root));

  delay(200);
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
  
//  if (JOY_Y <= JOY_X) {
//    return DIR_FORWARD;
//  } else if (JOY_Y >= JOY_X) {
//    return DIR_BACKWARD;
//  } else if (JOY_X < JOY_Y) {
//    return DIR_LEFT;
//  } else {
//    return DIR_RIGHT;
//  }
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
