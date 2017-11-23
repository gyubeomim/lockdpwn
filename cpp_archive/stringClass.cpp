/*
	열혈 c++ p510 #include <string> 에서 string 클래스 실제로 구현해보기. (다양한 대입연산자를 활용해)
*/
#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;

class String
{
private:
	int len;
	char * str;


public:
	String()    // 초기생성자
	{
		len = 0;
		str = NULL;
	}

	String(const char *s)		// 문자열(포인터)를 이용해 초기화시키는 경우 (String s1 = "IM";) 
	{
		len = strlen(s) + 1;
		str = new char[len];
		strcpy_s(str, len, s);
	}

	String(const String& s)		// 복사생성자 String s1 = s2 같은 경우에 사용된다
	{
		len = s.len;
		str = new char[len];
		strcpy_s(str, 100, s.str);
	}


	~String()
	{
		if (str != NULL)
		{
			delete []str;
		}
	}


	String& operator=(const String& s)   // s1 = s2 에 대한 대입연산자
	{
		len = s.len;

		if (str != NULL)
		{
			delete[]str;
		}

		str = new char[len];
		strcpy_s(str, 100, s.str);
		return *this;
	}

	String& operator+=(const String& s)  // s1 += s2 에 대한 대입연산자
	{
		len += s.len -1;
		
		char* tempstr = new char[len];
		
		strcpy_s(tempstr, 100, str);
		strcat_s(tempstr, 100, s.str);

		if (str != NULL)
		{
			delete[]str;
		}

		str = tempstr;

		return *this;
	}


	bool operator==(const String& s)	// s1 == s2 에 대한 대입연산자
	{
		return strcmp(str, s.str) ? false : true;  
		
		/*
		if (strcmp(str, s.str) == 0)
		{
			return true;
		}

		return false;
		*/
	}


	String operator+(const String& s)	// s1 + s2에 대한 대입연산자
	{
		char *newstr = new char[len + s.len - 1];

		strcpy_s(newstr, 100, str);
		strcat_s(newstr, 100, s.str);

		String tempstr(newstr);		// String tempstr = newstr 과 같다
		delete[]newstr;

		return tempstr;

	}


	friend ostream& operator<< (ostream& os, const String& s);
	friend istream& operator>>(istream& is, const String& s);

};




ostream& operator<< (ostream& os, const String& s)
{
	os << s.str;
	return os;
}


istream& operator>>(istream& is, String& s)
{
	char str[100];
	is >> str;

	s = String(str);

	return is;
}


int main()
{
	String str1 = "My name is ";
	String str2 = "Edward yoman";
	String str3 = str1 + str2;

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	str1 += str2;

	if (str1 == str3)
	{
		cout << "Those are same SENTENCES" << endl;
	}
	else
	{
		cout << "Those aren't same guys.." << endl;
	}

	String str4;
	cout << "문자열 입력: ";
	cin >> str4;
	cout << "입력한 문자열: " << str4 << endl;

	return 0;

}


















