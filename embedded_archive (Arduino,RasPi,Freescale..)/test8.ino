/*
 	arduino c ==> IR 리모콘 수신 코드  
				  (-)라고 써져있는건 GND
					그 옆에건 VCC
					S라고 써져있는건 A0 포트로
 */
#include <IRremote.h>

int readIR;
int RECV_PIN = 14; // A0 핀
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn();
}

void loop()
{
	if(irrecv.decode(&results))
	{
		if(results.decode_type == NEC)
		{
			switch(results.value)
			{
				case 0x00FF6897:
					Serial.println("Press '0'");
					break;
				case 0x00FF30CF:
					Serial.println("Press '1'");
					break;
				case 0x00FF18E7:
					Serial.println("Press '2'");
					break;
				case 0x00FF7A85:
					Serial.println("Press '3'");
					break;
				case 0x00FF10EF:
					Serial.println("Press '4'");
					break;
				case 0x00FF38C7:
					Serial.println("Press '5'");
					break;
				case 0x00FF5AA5:
					Serial.println("Press '6'");
					break;
				case 0x00FF42BD:
					Serial.println("Press '7'");
					break;
				case 0x00FF4AB5:
					Serial.println("Press '8'");
					break;
				case 0x00FF52AD:
					Serial.println("Press '9'");
					break;
				default:
					break;
			}
		}
		irrecv.resume();
	}
}
