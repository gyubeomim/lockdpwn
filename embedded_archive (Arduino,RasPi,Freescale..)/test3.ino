/*
 	arduino ==> 초음파센서로 거리읽는 코드
 */

// 초음파센서의 TRIG를 7번, ECHO를 6번 핀으로 선언합니다
#define TRIG 7
#define ECHO 6
 
void setup(){
    // Serial 모니터를 9600 bps로 설정합니다
    Serial.begin(9600);
    
    // TRIG는 OUTPUT, ECHO는 INPUT으로 설정합니다
    pinMode(TRIG,OUTPUT);
    pinMode(ECHO,INPUT);
}
 
void loop(){
    // 초음파센서의 거리값을 읽어오는 코드
    // TRIG의 값이 빠른속도로 ON/OFF되면서 초음파를 발사합니다
    digitalWrite(TRIG,LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG,HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIG,LOW);
 
    // ECHO에서 TRIG의 초음파를 읽으면 HIGH가 되는데 이 신호를 읽어서
    // 실제 거리 cm로 변환합니다
    long distance = pulseIn(ECHO,HIGH,5800)/58;
 
    // Serial 모니터에 거리값을 표시합니다
    Serial.print("d: ");
    Serial.print(distance);
    Serial.print("cm\n");
    
    // loop를 도는 속도가 너무 빠르므로 delay로 0.015정도로 늦춰줍니다
    delay(15);
}
