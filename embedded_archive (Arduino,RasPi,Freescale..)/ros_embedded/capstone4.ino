/*
  arduino ==> 캡스톤, 평균이동필터를 사용해 초음파센서를 안정시키고 거리값을 읽어 서보모터를 구동시키는 예제코드
*/
#include <Servo.h>  // 서보모터를 사용하는 헤더

// 최대값 15
// TRIG 2번 , ECHO 3번 핀으로 설정합니다
#define MAXNUM 15
#define TRIG 2
#define ECHO 3

// Servo 모터 객체를 선언합니다
Servo myservo;
int pos;
int i =0 ;
float dist;							// 센서를 통해 얻은 거리값
float distFiltered[MAXNUM] = {0}; // 평균이동필터로 필터링된 거리값
float final = 0; 					// 최종 서보모터에 입력되는 거리값

void setup(){
  // 초음파센서의 TRIG를 OUTPUT으로 ECHO를 INPUT으로 설정합니다
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  // 서보모터를 9번핀으로 설정합니다
  myservo.attach(9);

  // 시리얼모티러를 9600bps로 설정합니다
  Serial.begin(9600);
}

// 배열을 받아 배열 안에 있는 모든 수의 평균을 반환하는 함수
float getMean(float dist[]) {
  float sum = 0;
  for(int k = 0 ; k < MAXNUM ; k++)
  {
    sum += dist[k];
  }

  return sum / MAXNUM;
}

void loop(){
  // 초음파센서로부터 거리를 읽어오는 코드
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG,LOW);
  // cm 단위로 환산하기 위해 58.82로 나눠줍니다
  dist = pulseIn(ECHO,HIGH)/58.82;

  // distFiltered[] 배열에 거리값을 저장합니다
  distFiltered[i++] = dist;

  if (i > MAXNUM)
    i = 0;

  // distFiltered[] 배열 안의 값의 평균을 final에 저장합니다
  final = getMean(distFiltered);

  // final * 3 값을 서보모터에 입력합니다
  myservo.write(final * 3);
  // 시리얼모니터를 통해 확인합니다
  Serial.println(final);
}
