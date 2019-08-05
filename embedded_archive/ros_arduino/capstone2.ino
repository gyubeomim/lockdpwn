/*
   arduino ==> 캡스톤, 16 세그먼트를 1초에 1씩 증가시키는 코드
 */

volatile int STATE =  LOW;

// 2 ~ 13번 핀을 OUTPUT으로 설정하고 시리얼모니터를 9600bps로 설정합니다 
void setup()
{
	for(int i=2; i<13; i++)
	{
		pinMode(i, OUTPUT);
	}	
	Serial.begin(9600);
}

// 2~13의 핀을 HIGH로 설정합니다 애노드 타입이므로 전부 OFF됩니다
void reset()
{
	for(int i=2; i<13; i++)
	{
			digitalWrite(i, HIGH);
	}	
}

// a값(0 ~ 9)에 따라 LED를 숫자모양으로 켜는 함수 
// 숫자에 해당하는 부분을 LOW로 설정해 불이 켜지게 합니다
void LEDControl(int a)
{
	reset();

	if(a == 1)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 4 or i == 5)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 0)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 3 or i == 6 or i == 9 or i == 7 or i == 8 or i == 5 or i == 4)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	
	}
	else if(a == 2)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 3 or i == 6 or i== 5 or i ==10 or i == 11 or i == 7 or i==8)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 3)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 3 or i == 6 or i == 5 or i == 10 or i == 11 or i == 4 or i == 8)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 4)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 9 or i == 11 or i == 10 or i == 5 or i == 4)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}	
	}
	else if(a == 5)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i == 4 or i == 8)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 6)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i == 7 or i == 4 or i == 8)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 7)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 3 or i == 9 or i == 6 or i == 5 or i == 4)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 8)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			digitalWrite(i, LOW);
		}
	}
	else if(a == 9)
	{
		for(int i = 2; i <= 13 ; i++)
		{
			if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i== 5 or i== 4)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
}

// 1초 간격으로 16 segment에 0 ~ 9의 숫자를 표시합니다
void loop()
{
	for(int i = 0 ; i <= 9 ; i++)
	{
		LEDControl(i);
		delay(1000);
	}
}


