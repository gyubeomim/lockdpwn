/*
  c++ stl p208 deque 컨테이너 처음 사용해본 예제 코드
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

  dq


  for(deque<int>::size_type i = 0 ; i< dq.size() ;i++)
  {
    cout << dq[i] << ' ';
  }
  cout<<endl;


  return 0;
}
