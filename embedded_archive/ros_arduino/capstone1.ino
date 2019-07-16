/*
	arduino ==> 캡스톤, 12번과 7번핀, 스위치와 LED를 사용해 LED를 껏다 켯다 하는 코드
						그 다음 인터럽트를 사용해 스위치를 누를 떄마다 LED 끄고 키는 코드
*/
volatile int STATE = LOW;    // STATE에 LOW값을 저장합니다

void setup()
{
	pinMode(12, OUTPUT);     // 12번 핀을 OUTPUT으로 설정합니다
	pinMode(7,INPUT);
	//attachInterrupt(0, blink, CHANGE); // 2번핀의 신호가 변할 때마다 blink 함수를 실행합니다.
}

// STATE의 상태를 HIGH <==> LOW로 토글하는 함수
void blink()
{
	STATE = !STATE;
}

// 12번 핀의 상태를 STATE (HIGH, LOW)로 설정합니다
void loop()
{
	if(digitalRead(7))
	{
		blink();
	}
	digitalWrite(12,STATE);
}

