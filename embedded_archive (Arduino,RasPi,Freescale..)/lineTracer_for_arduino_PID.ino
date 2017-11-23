/*
  arduino ==> (not used) 라인트레이서를 PID제어를 통해 구현한 코드 (정상적으로 작동하지 않는다)
               정확한 PID값을 선정하고 switch 구문을 조금 더 수정해야 될 것 같다
*/
 
#include <PID_v1.h>            // PID 제어를 사용하기 위한 라이브러리 선언
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
 
 
//------------------------------------------------------------
// PID 제어용 변수 선언
double kp = 60;
double ki = 10;
double kd = 4;
 
// PID 제어용 input, output 변수를 선언합니다
double setpoint = 0;
double input_left, output_left;
double input_right, output_right;
 
// PID값을 설정해준다
PID pid_left(&input_left, &output_left, &setpoint, kp, ki, kd, DIRECT);
PID pid_right(&input_right, &output_right, &setpoint, kp, ki, kd, DIRECT);
 
// 모터 제어용 변수 선언
// EnA, EnB는 속도제어용(pwm), IN1,2,3,4는 방향제어용 핀입니다
int ENA = 10;
int ENB = 11;
 
int IN1 = 12;
int IN2 = 7;
int IN3 = 9;
int IN4 = 8;
 
// motorController 객체 생성, 맨 끝 파라미터 1,1은 각각 좌측, 우측모터의 최대속도(%) 입니다.
LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
 
 
// 적외선 센서값을 읽어서 tracesensor 구조체 안에 저장하는 함수
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
 
  // 오른쪽바퀴와 왼쪽바퀴의 PID제어를 위해 Sampling Time과 최대, 최저 output값을 초기화한다
  pid_left.SetMode(AUTOMATIC);
  pid_left.SetSampleTime(10);
  pid_left.SetOutputLimits(0, MAX_SPEED);
 
  pid_right.SetMode(AUTOMATIC);
  pid_right.SetSampleTime(10);
  pid_right.SetOutputLimits(0, MAX_SPEED);
 
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
      input_left += 0;
      input_right -= 0;
 
      Serial.print(leftFlag);
      Serial.println(rightFlag);
 
      break;
      // 전부 검정색인 경우
    case 0b00000:
      input_left += 0;
      input_right -= 0;
      break;
 
      // 정중앙에 검정선이 있는 경우
    case 0b11011:
      input_left -= 5;
      input_right -= 5;
 
      rightFlag = 0;
      leftFlag = 0;
      break;
 
    case 0b01111:
      input_left -= 5;
      input_right += 5;
 
      rightFlag = 1;
      leftFlag = 0;
      break;
 
    case 0b00111:
      input_left -= 2.5;
      input_right += 2.5;
      break;
 
    case 0b00011:
      input_left -= 2;
      input_right += 2;
      break;
 
    case 0b10011:
      input_left -= 1;
      input_right += 1;
      break;
 
    case 0b11001:
      input_left += 1;
      input_right -= 1;
      break;
 
    case 0b11000:
      input_left += 2;
      input_right -= 2;
      break;
 
    case 0b11100:
      input_left += 2.5;
      input_right -= 2.5;
      break;
 
    case 0b11110:
      input_left += 5;
      input_right -= 5;
 
      rightFlag = 0;
      leftFlag = 1;
      break;
 
    case 0b11101:
      input_left += 3;
      input_right -= 3;
      break;
 
    case 0b10111:
      input_left -= 3;
      input_right += 3;
      break;
 
    default:
      input_left += 0;
      input_right -= 0;
      break;
  }
    
 
  // 위에서 switch문을 통해 바퀴의 방향과 속도를 제어하기 위한 input_left, right의 가중치를 줍니다
  // input 값이 너무 커지는걸 방지하기 위해 아래와 같이 어느 정도가 넘어가면 0으로 초기화시킵니다. (불명확한 코드. 수정이 필요할 수도 있습니다)
  if(input_left >= 100 || input_left <= -100) input_left = 0;
  if(input_right >= 100 || input_right <= -100) input_right = 0;
 
 
  // 위의 input값을 통해 PID제어를 하면서 output값을 뽑아냅니다
  pid_left.Compute();
  pid_right.Compute();
 
 
 
  // move(a,b,minSpeed)  a : 위에서봤을 때 오른쪽
  //                     b : 위에서봤을 때 왼쪽
  if(rightFlag == 1 && leftFlag == 0)
    motorController.move(0, -MAX_SPEED, MIN_SPEED);
  else if(rightFlag == 0 && leftFlag == 1)
    motorController.move(-MAX_SPEED, 0, MIN_SPEED);
  else
    motorController.move(-output_right, -output_left, MIN_SPEED); // pid 연산으로 나온 output 값을 motorController로 전송합니다. (모터제어)
 
 
 
  // 속도가 너무 빨라서 디버깅이 어려울 경우 아래 코드를 사용합니다
  //    delay(1000);
 
 
  // 시리얼모니터 디버깅용 print 코드들
  Serial.print("i_left , i_right : ");
  Serial.print(input_left);
  Serial.print("     ");
  Serial.println(input_right);
  Serial.print("                     o_left , o_right : ");
  Serial.print("     ");
  Serial.print(output_left);
  Serial.print("     ");
  Serial.println(output_right);
}
