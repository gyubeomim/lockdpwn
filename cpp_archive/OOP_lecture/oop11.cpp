/*
 * c++ ==> 객체지향, b = +(2,a) 연산을 수행하기 위해 전역변수로 operator+를 선언한 예제 코드
 *                   헷갈헷갈
 */
#include <iostream>

using namespace std;
class Power 
{
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	friend Power operator+(int op1, Power op2); // 프렌드 선언
};

void Power::show() 
{
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

// 전역함수로 만들어야 한다
Power operator+(int op1, Power op2)
{
	Power tmp; // 임시 객체 생성
	tmp.kick = op1 + op2.kick; // kick 더하기
	tmp.punch = op1 + op2.punch; // punch 더하기
	return tmp; // 임시 객체 리턴
}

int main() 
{
	Power a(3, 5), b;
	a.show();
	b.show();
	// b = 2.+(a)와 같은 연산이 불가능하므로 전역함수로 operator+를 선언해줘야 한다 
	b = 2 + a; // 파워 객체 더하기 연산
	a.show();
	b.show();
}
