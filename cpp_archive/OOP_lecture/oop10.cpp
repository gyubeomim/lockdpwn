/*
 * c++ ==> 객체지향, 연산자중복을 사용해서 Power 클래스를 작성해본 예제 코드
 */
#include <iostream>
using namespace std;

class Power
{
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0)
	{
		this->kick = kick;
		this->punch = punch;
	}
	void show();
	Power operator+(int op2);
	Power operator++(int x);
	bool operator!();
};

void Power::show()
{
	cout << "kick= " << kick << ',' << " punch= " << punch << endl;
}

Power Power::operator+(int op2)
{
	Power tmp;
	tmp.kick = kick + op2;
	tmp.punch = punch + op2;
	return tmp;
}

bool Power::operator!()
{
	if(kick == 0 && punch == 0) return true;
	else return false;
}

int main(int argc, const char *argv[])
{
	Power a(3, 5), b;
	a.show();
	b.show();

	b = a + 2;
	a.show();
	b.show();

	Power c(0,0) , d(5,5);
	if(!c) cout << "c의 파워가 0이다" << endl;
	else   cout << "c의 파워가 0이 아니다" << endl;
	if(!d) cout << "d의 파워가 0이다" << endl;
	else   cout << "d의 파워가 0이 아니다" << endl;

	return 0;
}




