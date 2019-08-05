/*
  c++ ==> c++11 에서 rvalue reference를 설명하기 위한 예제 코드

          Number operator+(Number& rhs){} 부분이 컴파일 에러가 나서 진해하지 못하고 있다

  code from [http://bunhere.tistory.com/410?category=410931]
*/
#include <iostream>
using namespace std;

class Number {
 public:
  explicit Number(int i)
      : m_number(new int(i)) {
    cout << "Number Constructor is called(" << i << ")" << endl;
  }

  ~Number() {
    if (m_number)
      cout << "Number Destructor is called(" << *m_number << ")" << endl;
    delete m_number;
  }

  // ed: lvalue reference
  Number(const Number& rhs)
      : m_number(new int(*rhs.m_number)) {
    cout << "Number copy constructor is called" << endl;
  }

  // ed: rvalue reference
  Number(Number&& rhs) {
    std::cout << "Number move contructor is called" << endl;
    m_number = rhs.m_number;
    rhs.m_number = nullptr;
  }

  Number operator+(Number& rhs) {
    return Number(this->m_number + rhs.m_number);
  }

  /* static void printValue(Number n) { */
  /*   cout << "print " << *n.m_number << endl; */
  /* } */

  static void printValue(const Number& n) {
    cout << "print " << *n.m_number << endl;
  }

 private:
  int* m_number;

};

Number make_number() {
  return Number(2);
}

int main() {
  Number one(1);
  Number two(2);

  /* Number::printValue(one); // (1) */
  Number value(make_number()); // (2)
  /* Number sum(one + two); // (3) */
}
