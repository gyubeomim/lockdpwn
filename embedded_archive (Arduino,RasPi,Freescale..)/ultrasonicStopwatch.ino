/*
  arduino ==> 초음파센서 2개를 사용해서 스탑워치를 구현한 코드
              천장에서 물체를 떨어뜨리면 스탑워치를 시작해서 바닥에 떨어지는 순간까지 시간을 잰다
*/
#define TRIGBOTTOM 8
#define ECHOBOTTOM 9
#define TRIGUPPER 10
#define ECHOUPPER 11

#define COUNTLIMIT 1         // 카운트반복 횟수

long elapsedTime = 0;        // 경과시간
long previousMillis = 0;     // 시간차이
int distCounter = 0;         // 반복적으로 거리를 읽은 횟수
int distUpCounter = 0;       // 반복적으로 거리를 읽은 횟수, 천장용
int startFlag = 0;           // previousMillis 값을 구하기 위한 제어변수
int fractional;              // 소숫점자리수
double distance = 0;         // 초음파센서 거리값
double distanceUpper = 0;    // 초음파센서 거리값, 천장용
int upFlag = 0;              // 천장용 초음파센서 제어 플래그

void setup(){
  Serial.begin(9600);
  pinMode(TRIGUPPER,OUTPUT);
  pinMode(ECHOUPPER,INPUT);
  pinMode(TRIGBOTTOM,OUTPUT);
  pinMode(ECHOBOTTOM,INPUT);
}

void loop(){
  digitalWrite(TRIGUPPER,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGUPPER,HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIGUPPER,LOW);
  // 천장 위에 초음파 센서로 거리재는 코드
  distanceUpper = pulseIn(ECHOUPPER,HIGH,5800)/58.0;

  digitalWrite(TRIGBOTTOM,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGBOTTOM,HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIGBOTTOM,LOW);
  // 아래 초음파, 초음파센서로부터 거리를 재는 코드
  distance = pulseIn(ECHOBOTTOM,HIGH,5800)/58.0;

  /// 스톱워치 시간을 재는 코드
  elapsedTime = millis();

  // 천장센서에 물체가 인식되면 upFlag값이 증가한다
  if(distanceUpper != 0 && distanceUpper <= 50)
  {
    upFlag++;
  }

  // 천장의 센서를 읽으면 distUpCounter를 증가시킵니다.
  if(upFlag <= COUNTLIMIT && distanceUpper >= 0.5 && distanceUpper <= 50)
  {
    Serial.print("distUpper :[ ");
    Serial.print(distanceUpper);
    Serial.println(" cm ]");
    distUpCounter++;
  }

  /// 천장에 센서가 읽기 시작하면 previousMills값을 구하기 위한 코드
  if (distUpCounter >= COUNTLIMIT && startFlag == 0)
  {
    Serial.println("< START! >");
    previousMillis = elapsedTime;
    startFlag = 1;
  }

  // 물체가 떨어져서 바닥의 센서를 읽으면 distCounter를 증가시킵니다.
  if(distance != 0 && distance <= 50 && upFlag >= COUNTLIMIT)
  {
    Serial.print("dist :[ ");
    Serial.print(distance);
    Serial.println(" cm ]");
    distCounter++;
  }

  // 바닥에 닿는 순간 스탑워치를 종료하고 값을 출력한다
  if(distCounter >= COUNTLIMIT)
  {
    upFlag = 0;
    startFlag = 0;
    distUpCounter = 0;
    distCounter = 0;

    elapsedTime -= previousMillis;
    /// elapsedTime은 4자리 숫자이다 ex) 1234, 그 중에 천의 자리만 추출한다
    Serial.print("                  Elapsed Time : [ ");
    Serial.print( (int)(elapsedTime / 1000L));
    Serial.print(".");

    /// 나머지 소수점자리를 제어하기 위한 코드들
    fractional = (int)(elapsedTime % 1000L);

    if (fractional == 0)
    {
      Serial.print("000");      // add three zero's
    }
    else if (fractional < 10)
    {
      Serial.print("00");       // add two zeros
    }
    else if (fractional < 100)
    {
      Serial.print("0");        // add one zero
    }
    /// 소수점 자리 출력
    Serial.print(fractional);
    Serial.println(" sec ]");

    delay(2000);
    Serial.println("-------------------------------------------------");
    Serial.println("< READY! >");
  }
}
