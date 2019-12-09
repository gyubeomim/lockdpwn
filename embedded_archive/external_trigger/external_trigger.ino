int pin=3;

void setup() {
	Serial.begin(115200);
	pinMode(pin, OUTPUT);
}

void loop() {
  digitalWrite(pin, LOW);
  delay(30);  // ms
  digitalWrite(pin, HIGH);
}
