/*
 * c++ ==> 객체지향수업, EvenRandom 클래스를 생성해 최소값과 최대값 사이의 짝수인 난수를 10개 발생시키는 코드
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// EvenRandom 클래스를 생성합니다.
class EvenRandom
{
private:
	int maximum;    // 최대난수값을 제한하는 변수 선언
	int minimum;	// 최소값 선언
	int tmpNum;		// 임의의 변수 선언
	int *EvenNums; 	// 결과값을 가질 배열 선언

public:
	EvenRandom(int max, int min); // 생성자
	~EvenRandom();				  // 소멸자
	void printEvenNumbers();	  // 결과값 출력하는 멤버함수

};

// 생성자
EvenRandom::EvenRandom(int max, int min)
	: maximum(max), minimum(min)
{
	EvenNums = new int[10];
}

// 소멸자
EvenRandom::~EvenRandom()
{
	delete[] EvenNums;
}

// 멤버함수
void EvenRandom::printEvenNumbers()
{
	int i = 0;

	srand((unsigned)time(NULL)); // 난수를 발생시키기 위한 코드
	while (true)
	{
		tmpNum = rand() % maximum;   // 최대난수값을 제한해서 tmpNum에 담는다

		if (tmpNum % 2 == 0 && tmpNum > minimum)  // 최소값보다 크거나 짟수이면 EvenNums 배열에 저장한다
		{
			EvenNums[i++] = tmpNum;
		}

		if (i >= 10)  // EvenNums 배열이 10개가 꽉차면 루프를 종료한다
		{
			break;
		}
	}

	cout << "[*] "<< minimum << " 부터 " << maximum << " 까지의 짝수인 난수 10개는 " << endl;
	for (int j = 0; j < 10; j++)
	{
		cout << EvenNums[j] << " ";
	}
	cout << " 입니다" << endl;
}

int main(int argc, const char *argv[])
{
	int max, min;

	while (1)
	{
		cout << "[+] 난수의 최대값과 최소값을 설정해주세요 a,b : ";
		cin >> max >> min;

		if (max > min)
		{
			break;
		}
		else
		{
			cout << "[-] 다시 입력해주세요" << endl;
		}
	}
	EvenRandom er(max,min); // 최대,최소값을 가진 객체를 생성한다
	er.printEvenNumbers();  // 값을 출력한다

	return 0;
}

