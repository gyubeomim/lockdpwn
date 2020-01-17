/*
  arduino ==> 캡스톤, 모터의 회전을 홀센서로 읽어들인 다음 저역통과필터를 통해 서보모터를 구동하는 코드
 */
#include <MsTimer2.h>  // 타이머를 사용하는 헤더
#include <Servo.h>    // 서보모터를 사용하는 헤더

#define ALPHA 0.3 // 저역통과필터의 alpha 값을 0.3으로 설정한다

// Servo 모터의 myservo 객체를 선언한다
Servo myservo;
int n = 0;
int dt = 100;
float rpm = 0;
float LPFvalue = 0; // Low Pass Filter의 값

// DC모터가 회전하면서 Hall 센서를 통해 자석의 값을 읽어들여 모터의 RPM을 구하는 함수
void getRpm(){
  // rpm이므로 60을 곱합니다.
  // 극이 2개이므로 2로 나눕니다 (밀리세컨이므로 1000으로 나눕니다)
  rpm = (n * 60) / (dt * 0.002);
  Serial.println(rpm);

  // Low Pass Filter를 사용해 LPFvalue에 저장합니다
  LPFvalue = (1 - ALPHA) * LPFvalue +  ALPHA * rpm/30.0;
  n = 0;
}

// 인터럽트가 발생할 때마다 n값을 1씩 증가시키는 함수
void Encoder(){
  n += 1;
}

void setup(){
  Serial.begin(115200);					// 시리얼모티러를 115200bps로 설정합니다
  attachInterrupt(0, Encoder, CHANGE); // 2번핀의 신호가 변하면 Encoder 함술를 실행합니다
  MsTimer2::set(dt, getRpm);			// 0.1초에 한 번씩 getRpm() 함수를 실행하는 타이머를 설정합니다
  MsTimer2::start();					// 타이머를 실행합니다
  myservo.attach(9);					// 서보모터를 9번 핀에 설정합니다
}

void loop(){
  myservo.write(LPFvalue);  // Low Pass Filter를 통과한 값을 서보모터에 입력합니다
}
