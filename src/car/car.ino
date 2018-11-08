const int BDG_IN1 = 4;
const int BDG_IN2 = 5;
const int BDG_IN3 = 6;
const int BDG_IN4 = 7;

void setup() {
  pinMode(BDG_IN1, OUTPUT);
  pinMode(BDG_IN2, OUTPUT);
  pinMode(BDG_IN3, OUTPUT);
  pinMode(BDG_IN4, OUTPUT);
}

void loop() {
  testMotors();
}

void testMotors() {
  moveForward();
  delay(2000);
  
  stopMotors();
  delay(500);
  
  moveBackward();
  delay(2000);
  
  stopMotors();
  delay(500);

  turnRight();
  delay(2000);

  stopMotors();
  delay(500);

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
  digitalWrite(BDG_IN1, LOW);
  digitalWrite(BDG_IN2, HIGH);

  digitalWrite(BDG_IN3, HIGH);
  digitalWrite(BDG_IN4, LOW);
}

void turnLeft() {
  digitalWrite(BDG_IN1, HIGH);
  digitalWrite(BDG_IN2, LOW);

  digitalWrite(BDG_IN3, LOW);
  digitalWrite(BDG_IN4, HIGH);
}

void stopMotors() {
  digitalWrite(BDG_IN1, HIGH);
  digitalWrite(BDG_IN2, HIGH);

  digitalWrite(BDG_IN3, HIGH);
  digitalWrite(BDG_IN4, HIGH);
}
