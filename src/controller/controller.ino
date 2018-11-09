#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// Joystick
const int JOY_PIN1 = A0;
const int JOY_PIN2 = A1;
const int JOY_PIN3 = 7;
int JOY_X;
int JOY_Y;
int JOY_SW;


// nRF24L01+
const int NRF_CE = 5;
const int NRF_CSN = 6;

RF24 radio(NRF_CE, NRF_CSN);

const byte address[6] = "00001";


void setup() {
  pinMode(JOY_PIN3, INPUT_PULLUP);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Serial.begin(9600);
}


void loop() {
  JOY_X = analogRead(JOY_PIN1);
  JOY_Y = analogRead(JOY_PIN2);
  JOY_SW = digitalRead(JOY_PIN3);

  Serial.print("X: ");
  Serial.println(JOY_X);

  Serial.print("Y: ");
  Serial.println(JOY_Y);

  Serial.print("SW: ");
  Serial.println(JOY_SW);

  const char text[] = "ayy lmao";
  radio.write(&text, sizeof(text));

  delay(200);
}
