/*
   arduino ==> 캡스톤, 16 세그먼트를 1초에 1씩 증가시키면서 스위치를 누르면 다시 0부터 시작하는 코드
*/
#include <MsTimer2.h> // 타이머를 사용하는 헤더

// 전역변수 i를 0으로 선언합니다
int i = 0;

// i값을 0으로 초기화시키는 함수
void InitializeZero()
{
	i = 0;
}

// 12번 핀을 제외한 모든 핀을 HIGH로 설정합니다
// 애노드 타입이므로 전부 OFF됩니다
void reset()
{
	for(int i=3; i<13; i++)
	{
		if (i == 12)
		{
			continue;
		}
		else 
		{
			digitalWrite(i, HIGH);
		}
	}	
}

// a값(0 ~ 9)에 따라 LED를 숫자모양으로 켜는 함수 
// 숫자에 해당하는 부분을 LOW로 설정해 불이 켜지게 합니다
void LEDControl(int a)
{
	reset();

	if(a == 1)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 4 or i == 5)
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
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 9 or i == 7 or i == 8 or i == 5 or i == 4)
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
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i== 5 or i ==10 or i == 11 or i == 7 or i==8)
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
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 5 or i == 10 or i == 11 or i == 4 or i == 8)
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
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 9 or i == 11 or i == 10 or i == 5 or i == 4)
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
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i == 4 or i == 8)
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
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i == 7 or i == 4 or i == 8)
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
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 9 or i == 6 or i == 5 or i == 4)
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
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else 
			{
				digitalWrite(i, LOW);
			}
		}
	}
	else if(a == 9)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i== 5 or i== 4)
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

// 0 ~ 9까지 i값을 증가시키면서 16 segment에 불을 켜는 함수
void IncreaseNumber()
{
	LEDControl(i++);

	if (i > 9)
	{
		i = 0;
	}
}

void setup()
{
	// 3 ~ 13핀을 출력으로 설정합니다
	for(int i=3; i<13; i++)
	{
		pinMode(i, OUTPUT);
	}	

	MsTimer2::set(1000, IncreaseNumber);    // 1초에 한 번씩 IncreaseNumber() 함수를 실행합니다
	MsTimer2::start();						// 타이머를 시작합니다
	attachInterrupt(0, InitializeZero, HIGH); // 2번 핀의 스위치가 눌려지면 InitializeZero() 함수를 실행해서 i를 0으로 초기화합니다
}


void loop()
{}


