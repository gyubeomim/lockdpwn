/*
 * c++ ==> 객체지향수업, Calc 메인 
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include "calculatorSimple2.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
  int first, second;
  char op;

  Add a;
  Sub s;
  Mul m;
  Div d;

  while (1)
  {
    cout << endl;
    cout << "두 정수와 연산자를 입력하세요 >> ";
    cin >> first >> second >> op;

    if (isdigit(first) || isdigit(second))
    {
      cout << "다시 해주세요" << endl;
      continue;
    }
		
    if (!operatorChecker(op))
    {
      cout << "다시 해주세요" << endl;
      continue;
    }

    switch (op)
    {
      case '+':
        a.setValue(first, second);
        cout << a.calculate();
        break;
      case '-':
        s.setValue(first, second);
        cout << s.calculate();
        break;

      case '*':
        m.setValue(first, second);
        cout << m.calculate();
        break;

      case '/':
        d.setValue(first, second);
        cout << d.calculate();
        break;
    }
  }

  return 0;
}


