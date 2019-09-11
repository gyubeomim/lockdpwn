// DC motor control using PWM

int motorPin1 = 5;
int motorPin2 = 10;

void setup() {
	Serial.begin(115200);
	pinMode(motorPin1, OUTPUT);
	pinMode(motorPin2, OUTPUT);
}

void loop() {
	/* rotateLeft(i,100); */
	/* rotateRight(i,100); */

  rotateLeft(150, 500);
  Serial.println("1");
  rotateRight(50, 1000);
  Serial.println("2");
  rotateRight(150, 1000);
  Serial.println("3");
  rotateRight(200, 1000);
  Serial.println("4");
  rotateLeft(255, 500);
  Serial.println("5");
  rotateRight(10, 1500);
  Serial.println("6");
}

void rotateLeft(int speedOfRotate, int length){
  analogWrite(motorPin1, speedOfRotate); //rotates motor
  digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
  delay(length); //waits
  digitalWrite(motorPin1, LOW);    // set the Pin motorPin1 LOW
}

void rotateRight(int speedOfRotate, int length){
  analogWrite(motorPin2, speedOfRotate); //rotates motor
  digitalWrite(motorPin1, LOW);    // set the Pin motorPin1 LOW
  delay(length); //waits
  digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
}
