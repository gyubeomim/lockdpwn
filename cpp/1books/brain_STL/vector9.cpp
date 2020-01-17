/*
  c++ stl p201 vector ==> erase() 멤버함수를 이용해 원소를 삭제하는 예제 코드
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> ve;


  ve.push_back(100);
  ve.push_back(200);
  ve.push_back(300);
  ve.push_back(400);
  ve.push_back(500);



  vector<int>::iterator iter;
  vector<int>::iterator iter2;

  
  for(iter = ve.begin() ; iter != ve.end() ; ++iter)
  {
    cout<< *iter << " ";
  }
  cout<<endl;



  // 1
  iter = ve.begin() + 2;
  iter2 = ve.erase(iter);    // 현재 iter가 가르키는 원소를 제거하고 iter2는 그 주소를 가르킵니다
  
  for(iter = ve.begin() ; iter != ve.end() ; ++iter)
  {
    cout<< *iter << " ";
  }
  cout<<endl;



  // 2
  iter2 = ve.erase(ve.begin() + 1, ve.end());    // begin() + 1 부터 end()까지의 원소를 제거합니다

  for(iter = ve.begin() ; iter != ve.end() ; ++iter)
  {
    cout<< *iter << " ";
  }
  cout<<endl;

  
  return 0;
  
}
