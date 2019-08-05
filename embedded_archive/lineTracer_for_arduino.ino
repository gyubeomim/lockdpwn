/*
  arduino ==> 라인트레이서를 아두이노를 활용해 구현한 코드
*/
 
#include <LMotorController.h>  // 모터의 속도와 방향을 제어하기 위한 라이브러리 선언
#define MIN_SPEED 30             // 모터의 최저속도를 설정합니다 (0~255 범위)
#define MAX_SPEED 255          // 최고속도 (0~255 범위)
 
/*
   아두이노의 PWM신호는 0 ~ 255의 해상도를 가집니다.
   예를들어 5v의 최대전압을 모터에 줄 수 있을 경우 최대속도가 된다면

   0(min)    :  0v, 모터 정지
   ...
   128         :  2.5v, 모터 중간속도
   ...
   255(max)  :  5v, 모터 최대속도
*/
 
 
 
//---------------------------------------------------------------
// 라인트레이서 적외선센서 5개의 값을 읽을 변수 a,b,c,d,e를 선언합니다
int a,b,c,d,e;
 
// 오른쪽 끝, 왼쪽 끝에 있는 적외선센서 값이 읽힐 경우 1이 되는 Flag를 선언합니다
int rightFlag = 0;
int leftFlag = 0;
 
// 적외선 센서를 편리하게 사용하기 위한 구조체 선언
// 구조체로 선언해서 사용하는 것이 여러개의 적외선센서 값을 읽는데 편리해서 사용합니다
struct SENSOR{
  union{
    int R;
    struct{
      int sensor1:1;
      int sensor2:1;
      int sensor3:1;
      int sensor4:1;
      int sensor5:1;
    }B;
  }sen;
};
 
// SENSOR의 구조체 이름을 tracesensor로 선언합니다
struct SENSOR tracesensor;
 
// 모터 제어용 변수 선언
// EnA, EnB는 속도제어용(pwm), IN1,2,3,4는 방향제어용 핀입니다
int ENA = 10;
int ENB = 11;
 
int IN1 = 12;
int IN2 = 7;
int IN3 = 9;
int IN4 = 8;
 
 
// motorController 객체를 생성합니다
// 맨 끝 파라미터 1,1은 각각 좌측, 우측모터의 최대속도(%) 입니다.
LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
 
 
// 적외선 센서값을 읽어서 tracesensor 구조체 안에 저장하는 함수. 값을 읽을 경우 해당 위치에 1이 저장됩니다
void Sensing(){
  a=0;b=0;c=0;d=0;e=0;
 
  if(!digitalRead(2)){
    Serial.print("2 ");
    a = 1;
  }
  if(!digitalRead(3)){
    Serial.print("3 ");
    b = 1;
  }
  if(!digitalRead(4)){
    Serial.print("4 ");
    c = 1;
  }
  if(!digitalRead(5)){
    Serial.print("5 ");
    d = 1;
  }
 
  if(!digitalRead(6)){
    Serial.println("6");
    e = 1;
  }
 
  tracesensor.sen.B.sensor1 = a;
  tracesensor.sen.B.sensor2 = b;
  tracesensor.sen.B.sensor3 = c;
  tracesensor.sen.B.sensor4 = d;
  tracesensor.sen.B.sensor5 = e;
}
 
void setup() {
  // 시리얼모니터로 센서값이 제대로 읽히는지 확인하기 위해 (println함수로) 시리얼모니터를 사용한다고 선언
  Serial.begin(115200);
 
  // 아두이노와 적외선센서가 연결되는 핀들 선언
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
}
 
 
void loop() {
  // Sensing()함수를 호출해서 적외선센서값을 읽습니다
  Sensing();
 
  Serial.println(tracesensor.sen.R, BIN);
 
  // move(a,b,minSpeed)  a : 위에서봤을 때 오른쪽
  //                     b : 위에서봤을 때 왼쪽
  //                     (-) 값이 제가 꽂은 배선을 기준으로 앞으로 회전하는 방향이었습니다
  //                     -255 : 최대속도로 전진
  //                      255 : 최대속도로 후진
  switch(tracesensor.sen.R){
    // 전부 흰색인 경우
    case 0b11111:
      Serial.print("                           ");
      Serial.print(leftFlag);
      Serial.println(rightFlag);
 
      if(rightFlag == 0 && leftFlag == 1)
    motorController.move(MAX_SPEED - 90, -MAX_SPEED, MIN_SPEED);
      else if(rightFlag == 1 && leftFlag == 0)
    motorController.move(-MAX_SPEED, MAX_SPEED - 90, MIN_SPEED);
 
    break;
 
    // 전부 검정색인 경우
    case 0b00000:
      break;
 
    // 정중앙에 검정선이 있는 경우
    case 0b11011:
      Serial.println("11011");
      motorController.move(-MAX_SPEED, -MAX_SPEED, MIN_SPEED);
 
      rightFlag = 0;
      leftFlag = 0;
      break;
 
    // 가장자리1
    case 0b01111:
      Serial.println("01111");
      motorController.move(0, -MAX_SPEED, MIN_SPEED);
 
      rightFlag = 1;
      leftFlag = 0;
      break;
 
    case 0b00111:
      Serial.println("00111");
      motorController.move(0, -MAX_SPEED + 40, MIN_SPEED);
      break;
 
    case 0b10011:
      Serial.println("10011");
      motorController.move(0, -MAX_SPEED + 50, MIN_SPEED);
      break;
 
    case 0b11001:
      Serial.println("11001");
      motorController.move(-MAX_SPEED + 50, 0, MIN_SPEED);
      break;
 
    case 0b11100:
      Serial.println("11100");
      motorController.move(-MAX_SPEED + 40, 0, MIN_SPEED);
      break;
 
      // 가장자리2
    case 0b11110:
      Serial.println("11110");
      motorController.move(-MAX_SPEED, 0, MIN_SPEED);
 
      rightFlag = 0;
      leftFlag = 1;
      break;
 
    case 0b11101:
      Serial.println("11101");
      motorController.move(-MAX_SPEED + 30, 0, MIN_SPEED);
      break;
 
    case 0b10111:
      Serial.println("10111");
      motorController.move(0, -MAX_SPEED + 30, MIN_SPEED);
      break;
 
    default:
      motorController.move(0, 0, MIN_SPEED);
      break;
  }
    
  //    delay(1000);
}
