/*
  c++ stl p179 vector --> resize() 함수를 사용해서 객체의 크기를 변경하는 예제 코드
*/

#include <iostream>
#include <vector>


using namespace std;


int main()
{
  vector<int> ve(5);

  ve[0] = 10;
  ve[1] = 120;
  ve[2] = 1230;
  ve[3] = 12340;  
  ve[4] = 123450;


  for(vector<int>::size_type i = 0; i< ve.size() ;  ++i)
  {
    if(ve[i] == 0)
    {
      continue;
    }
    cout << ve[i] << endl;
  }
  cout<<endl;

  cout<< "size: "<<ve.size() <<" capacity: " << ve.capacity() << endl;




  
  ve.resize(10);   // ve 벡터객체의 크기를 변경한다

  for(vector<int>::size_type i = 0 ; i < ve.size() ; ++i)
  {
    if(ve[i] == 0)
    {
      continue;
    }
    cout<< ve[i] << endl;
  }
  cout << endl;
  cout<< "size: "<<ve.size() <<" capacity: " << ve.capacity() << endl;
  




  
  ve.resize(20);

  for(vector<int>::size_type i = 0 ; i < ve.size() ; ++i)
  {
    if(ve[i] == 0)
    {
      continue;
    }
    cout<< ve[i] << endl;
  }
  cout << endl;
  cout<< "size: "<<ve.size() <<" capacity: " << ve.capacity() << endl;

}
