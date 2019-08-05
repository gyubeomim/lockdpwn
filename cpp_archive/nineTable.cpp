/*
	기술이의 스킬랜드 - 예외(try, catch)를 이용한 구구단 소스코드
*/
#include "stdafx.h"
#include <iostream>


using namespace std;


int main()
{
  int input;

  while (1)
  {
    try
    {
      cout << "몇 단? ";
      cin >> input;


      if (cin.fail())
      {
        throw "error";
      }

      else if (input >= 1 && input <= 9)
      {
        for (int i = 1; i <= 9; i++)
        {
          cout << input << "x" << i << "=" << input*i << '\t';
        }

        cout << endl << endl;
      }

      else throw input;



    }


    catch (int e)
    {
      cout << e << "는 잘못된 입력입니다. 1~ 9 사이의 숫자만 입력하세요" << endl << endl;
    }

    catch (char *e)
    {
      cout << e << "는 잘못된 문자열 입력입니다. 1~ 9 사이의 숫자만 입력하세요" << endl << endl;
    }

    break;
  }


  return 0;
}












