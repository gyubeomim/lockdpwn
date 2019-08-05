/*
 	arduino ==> 가변저항을 돌려서 값을 읽는 코드
				가변저항을 핀들을 아래로 놨을 떄
				왼쪽께 GND, 오른쪽꼐 VCC, 중앙이 A0 포트
*/

void setup()
{
	Serial.begin(9600);
	pinMode(14,INPUT);
}

void loop()
{
	int value = analogRead(14);
	Serial.print(value);
	Serial.println("");
}



