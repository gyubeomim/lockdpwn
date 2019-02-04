/*
  c++ stl p151 역방향 반복자 reverse_iterator의 사용 코드
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

  for(vector<int>::iterator iter = ve.begin(); iter != ve.end() ; ++iter)
  {
    cout<< *iter << endl;
  }
  cout<< endl;

  reverse_iterator<vector<int>::iterator> riter(ve.end());        // 역방향 반복자 reverse_iterator의 활용
  reverse_iterator<vector<int>::iterator> end_riter(ve.begin());

  for( ; riter != end_riter ; ++riter)
  {
    cout<< *riter <<endl;
  }
  cout<< endl;  

  return 0;
}
