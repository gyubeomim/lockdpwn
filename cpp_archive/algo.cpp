/*
  c++ stl p143 find 알고리즘을 사용해 vector안에 있는 객체를 찾는 코드
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  vector<int> ve;



  ve.push_back(10);
  ve.push_back(20);
  ve.push_back(30);
  ve.push_back(40);
  ve.push_back(50);

  vector<int>::iterator iter;

  iter = find(ve.begin(), ve.end(), 20);    // find 알고리즘을 사용해 값을 찾는다

  cout<<*iter<<endl;


  iter = find(ve.begin(), ve.end(), 100);

  if (iter == ve.end())
  {
    cout<< "그런거 없음!"<<endl;
  }

  return 0;
  
}
