/*
	열혈 c++ p430 연산자 오버로딩을 사용해 cout, endl을 구현해보는 코드
*/
#include "stdafx.h"
#include <iostream>


namespace mystd
{
	using namespace std;

	class ostream
	{
	public:
		ostream& operator<< (char *str)
		{
			printf("%s", str);
			return *this;
		}

		ostream& operator<<(char str)
		{
			printf("%c", str);
			return *this;
		}

		ostream& operator<<(int num)
		{
			printf("%d", num);
			return *this;
		}

		ostream& operator<<(double e)
		{
			printf("%g", e);
			return *this;
		}

		ostream& operator<<(ostream& (*fp)(ostream &ostm))
		{
			return fp(*this);
		}
	};

	ostream& endl(ostream &ostm)
	{
		ostm << '\n';
		fflush(stdout);
		return ostm;
	}


	ostream cout;

	
}

int main()
{
	using mystd::cout;
	using mystd::endl;


	cout << "Simple";
	cout << endl;
	cout << 3.14;
	cout << endl;
	cout << 123;
	endl(cout);

}






