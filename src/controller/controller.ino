const int JOY_PIN1 = A0;
const int JOY_PIN2 = A1;
const int JOY_PIN3 = 7;
int JOY_X;
int JOY_Y;
int JOY_SW;

void setup() {
  pinMode(JOY_PIN3, INPUT_PULLUP);
  
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

  delay(200);
}
