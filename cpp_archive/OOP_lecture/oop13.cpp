/*
 * c++ ==> 객체지향, 추상클래스 Calculator를 상속받은 Adder와 Subtractor에서 가상함수 calc()를 구현한 코드
 */
#include <iostream>
using namespace std;

class Calculator{
	void input(){
		cout << "정수 2개를 입력하세요>> ";
		cin >> a >> b;
	}

protected:
	int a, b;
	virtual int calc(int a,int b) = 0;

public:
	void run(){
		input();
		cout << "계산된 값은 "  << calc(a,b) << endl;
	}
};

class Adder : public Calculator{
	virtual int calc(int a,int b) { return a + b; }
};

class Subtractor : public Calculator{
	virtual int calc(int a, int b) { return a - b; }
};

int main(int argc, const char *argv[]){
	Adder adder;
	Subtractor subtractor;
	adder.run();
	subtractor.run();

}

