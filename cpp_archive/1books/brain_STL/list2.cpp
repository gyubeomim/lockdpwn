/*
  c++ stl p227 list ==> remove() , remove_if() 멤버함수에 대한 예제 코드
 */
#include <iostream>
#include <list>

using namespace std;

bool Predicate(int n)
{
  return 10 <= n && n <= 30;
}


int main()
{
  list<int> lt;

  lt.push_back(10);
  lt.push_back(20);
  lt.push_back(30);
  lt.push_back(40);
  lt.push_back(50);
  lt.push_back(10);

  
  list<int>::iterator iter;

  for(iter = lt.begin(); iter != lt.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout << endl;



  lt.remove_if(Predicate);  // remove_if() : Predicate 함수를 이용해 참인 원소는 모두 제거합니다
  
  for(iter = lt.begin(); iter != lt.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout << endl;

  return 0;
}
