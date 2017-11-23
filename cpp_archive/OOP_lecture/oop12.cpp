/*
 * c++ ==> 객체지향, 추상클래스 Calculator를 사용해 이를 상속받은 GoodCalc를 구현한 코드
 */
#include <iostream>
using namespace std;

class Calculator{

public:
	virtual int add(int a, int b) = 0;
	virtual int subtract(int a ,int b) = 0;
	virtual double average(int a[], int size) = 0;
};


class GoodCalc : public Calculator{

	public:
		int add(int a, int b) { return a + b;};
		int subtract(int a,int b) { return a - b;};
		double average(int a[], int size){
			double sum = 0;
			for(int i = 0 ; i < size ;i++)
				sum += a[i];
			return sum;
		}
};

int main(int argc, const char *argv[])
{
	int a[] = {1,2,3,4,5};
	Calculator *p = new GoodCalc();
	cout << p->add(2,3) << endl;
	cout << p->subtract(2,3) << endl;
	cout << p->average(a,5) << endl;
	return 0;
}
