/*
	arduino ==> 적외선센서
 */

void setup(){
    // Serial 모니터를 9600 bps로 설정합니다
    Serial.begin(9600);
    // 2번 핀을 INPUT으로 설정합니다
    pinMode(2,INPUT);
}
 
void loop(){
    // 2번핀에 HIGH가 입력되면 OFF, LOW가 입력되면 ON을 출력하는 코드를 작성합니다
    if(!digitalRead(2)){
        Serial.print("ON\n");
    }
    else{
        Serial.print("OFF\n");
    }
}
