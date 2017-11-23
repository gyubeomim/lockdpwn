/*
 * arduino ==> 캡스톤, RC 카의 차량에 있는 서보모터, DC 3상모터 속도조절, 홀센서 데이터 받아오기를 테스트해 본 코드
*/
#include <Servo.h>
#include <MsTimer2.h>

int n = 0;
int dt = 100;
float rpm = 0;

Servo myservo;
Servo esc;

// DC모터가 회전하면서 Hall 센서를 통해 자석의 값을 읽어들여 모터의 RPM을 구하는 함수
void getRpm(){
  // rpm이므로 60을 곱합니다.
  // 극이 2개이므로 2로 나눕니다 (밀리세컨이므로 1000으로 나눕니다)
  rpm = (n * 60) / (dt * 0.002);

	  Serial.println(rpm);

  n = 0;
}

// 인터럽트가 발생할 때마다 n값을 1씩 증가시키는 함수
void Encoder(){
  n += 1;
}

void setup(){
	Serial.begin(9600);
	
	// 모터의 속도값을 읽기 위한 홀센서 선언
	attachInterrupt(0, Encoder, CHANGE);  // 2번 핀
	MsTimer2::set(dt, getRpm);
	MsTimer2::start();

	// Servo Motor 7번핀
	myservo.attach(7);

	// DC Motor Speed Control 8번핀
	esc.attach(8);
	esc.writeMicroseconds(1000);

}

void loop(){
//-----------------------------------------------
// 서보 모터 테스트 (45 ~ 85도의 각도로 움직인다)
/*
	for(int i = 45 ; i < 85 ; i++){
		myservo.write(i);
		Serial.println(i);
		delay(50);
	}
	for(int i = 85 ; i > 45 ; i--){
		myservo.write(i);
		Serial.println(i);
		delay(50);
	}
*/
//-----------------------------------------------
// DC모터 속도 테스트 (1500부터 작동해서 계속 가속된다)
	for(int i = 1400 ; i < 1700 ; i++){
		esc.writeMicroseconds(i);
		Serial.println(i);
		delay(20);
	}
	for(int i = 1700 ; i > 1400 ; i--){
		esc.writeMicroseconds(i);
		Serial.println(i);
		delay(20);
	}
}
