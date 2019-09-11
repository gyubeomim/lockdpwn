int input_value=0;
int led_pin=3;

void setup() {
	Serial.begin(115200);
	pinMode(led_pin, OUTPUT);
}

void loop() {
	input_value += 10;

	if(input_value > 250) {
		input_value = 0;
	}
	
	Serial.println(input_value);

	analogWrite(led_pin, input_value);

	delay(10); // 10ms
}
