/*
  c++ stl p189 vector ==> assign()을 사용해 객체 원소값을 할당하는 예제 코드
*/

#include <iostream>
#include <vector>


using namespace std;


int main()
{
  vector<int> ve(5,1);


  for(vector<int>::size_type i = 0 ; i< ve.size() ; ++i)
  {
    cout<< ve[i] << " ";
  }
  cout<< endl;

  ve.assign(5,200);


  for(vector<int>::size_type i = 0 ; i< ve.size() ; ++i)
  {
    cout<< ve[i] << " ";
  }
  cout<< endl;


  return 0;
  
}
