int pin=3;

void setup() {
	Serial.begin(115200);
	pinMode(pin, OUTPUT);
}

void loop() {
  digitalWrite(pin, LOW);
  delay(33);  // ms
  digitalWrite(pin, HIGH);
}
