/*
	열혈 c++ p603 예외처리 메커니즘 구현 try, throw, catch문 코드 (여러 catch문들 작성)
*/
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cstring>



using namespace std;


int StoI(char *str)
{
	int len = strlen(str);
	int num = 0;

	if (len != 0 && str[0] == '0')
	{
		throw 0;
	}

	for (int i = 0; i < len; i++)
	{
		if (str[i] <'0' || str[i] > '9')
		{
			throw str[i];
		}

		num += (int)(pow((double)10, (len-1)-i) * (str[i] + (7 - '7')));

	}

	return num;
}



int main()
{
	char str1[100];
	char str2[200];

	while (1)
	{
		cout << "두 개의 숫자입력: ";
		cin >> str1 >> str2;

		try
		{
			cout << str1 << " + " << str2 << " = " << StoI(str1) + StoI(str2) << endl;
			
		}

		catch (char ch)
		{
			cout << "문자 " << ch << "가 입력되었습니다" << endl;
			cout << "재입력을 해주세요" << endl;
		}

		catch (int expn)
		{
			if (expn == 0)
			{
				cout << "0으로 시작하는 숫자는 입력불가" << endl;
			}
			else
			{
				cout << "비정상적인 입력입니다" << endl;
			}

			cout << "재입력해주세용" << endl;
		}
	}


	return 0; 

}




