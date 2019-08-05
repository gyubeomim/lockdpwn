/*
	arduino ==> 적외선센서를 읽어서 작동하는지 확인하는 예제코드
 */

int segmentLEDs[] = { 6, 7, 8, 9,10,11,12, 5};
// 지정된 LED 개수
int segmentLEDsNum = 8;

// 각 숫자에 대한 LED 설정 값을 정의합니다.
// 숫자에 매칭되는 LED의 로직레벨을 LOW(0) 상태로 설정합니다.
int digitForNum[10][8] = {
	{0, 0, 0, 0, 0, 0, 1, 1}, //0
	{1, 0, 0, 1, 1, 1, 1, 1}, //1
	{0, 0, 1, 0, 0, 1, 0, 1}, //2
	{0, 0, 0, 0, 1, 1, 0, 1}, //3
	{1, 0, 0, 1, 1, 0, 0, 1}, //4
	{0, 1, 0, 0, 1, 0, 0, 1}, //5
	{0, 1, 0, 0, 0, 0, 0, 1}, //6
	{0, 0, 0, 1, 1, 1, 1, 1}, //7
	{0, 0, 0, 0, 0, 0, 0, 1}, //8
	{0, 0, 0, 0, 1, 0, 0, 1}  //9
};
int i =0 ;

void setup()
{
	Serial.begin(9600);
	pinMode(5,OUTPUT);
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(8,OUTPUT);
	pinMode(9,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(12,OUTPUT);
}

void loop()
{
	for (int i = 0 ; i < 10 ; i++) 
	{
		// 각 숫자에 대한 각각 LED의 로직레벨을 설정합니다.
		for (int j = 0 ; j < segmentLEDsNum ; j++) 
		{
			digitalWrite(segmentLEDs[j], digitForNum[i][j]);
		}
		// 1초 동안 대기합니다.
		delay(300);
	}

}
