/*
  c++ stl p215 deque ==> insert() 멤버함수를 사용한 예제 코드
 */
#include <iostream>
#include <deque>

using namespace std;

int main()
{
  deque<int> dq;

  for(deque<int>::size_type i = 0 ; i < 10 ; i++)
  {
    dq.push_back((i+1) * 10);
  }



  
  deque<int>::iterator iter;
  deque<int>::iterator iter2;

  for(iter = dq.begin() ; iter != dq.end() ; iter++)
  {
    cout<< *iter<<endl;
  }
  cout<<endl;


  
  iter = dq.begin() + 2;
  iter2 = dq.insert(iter,555);  // iter 주소에 555를 추가하고 iter2가 가르키게 합니다

  cout<< "["<< *iter2 <<"]"<<endl<<endl;


  
  for(iter = dq.begin() ; iter != dq.end() ; iter++)
  {
    cout<< *iter<<endl;
  }
  cout<<endl;
  
  return 0;
}
