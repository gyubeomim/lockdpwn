/*
  c++ ==> 열혈 c++ p644 다형성 추상클래스에서 형변환 dynamic_cast의 사용법
          dynamic_cast<...> 와 같이 형변환을 할 수 있다. 유도클래스 -> 기초클래스로
          하지만 추상클래스가 존재하면 기초 -> 유도도 가능하다
*/
#include <iostream>

using namespace std;

// 기초클래스 (virtual 함수가 있으므로 추상클래스이다)
class edward
{
 public:
  virtual void showSimpleInfo()
  {
    cout << "Edward Base class" << endl;
  }
};


// 유도클래스
class ashely : public edward
{
 public:
  void showSimpleInfo()
  {
    cout << "Ashely Derived class" << endl;
  }
};

int main()
{
  edward *ed = new ashely;   // ed는 ashely 객체를 가르키는 edward 포인터변수이다!
  ashely* ash = dynamic_cast<ashely*>(ed);     // edward 클래스가 추상클래스이므로 다음과 같이 기초 -> 유도로 형변환이 가능하다

  ash->showSimpleInfo();

  return 0;
}

