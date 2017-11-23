/*
  c++ stl p199 vector ==> insert() 멤버함수를 이용해 객체에 원소를 추가하는 예제코드
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


  vector<int>::iterator iter = ve.begin() + 2;

  ve.insert(iter,3,123);  // iter가 가르키는 곳에 정수 123을 3개 삽입한다

  for(iter = ve.begin(); iter != ve.end() ; ++iter)
  {
    cout<< *iter << endl;
  }
  cout<< endl;



  vector<int> ve2;
  
  ve2.push_back(1);
  ve2.push_back(2);
  ve2.push_back(3);


  iter = ve2.begin() + 1;


  ve2.insert(iter, ve.begin(), ve.end());   // ve.begin()부터 ve.end() 까지 구간의 원소를 ve2에 삽입한다

  for(iter = ve2.begin(); iter != ve2.end() ; ++iter)
  {
    cout<< *iter << endl;
  }
  cout<<endl;
  
  return 0;
  
}
