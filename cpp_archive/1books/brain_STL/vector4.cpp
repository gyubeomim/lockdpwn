/*
  c++ stl p181 vector ==> clear(), empty() 함수를 이용한 코드 예제
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



  ve.clear();

  cout<< "size: "<<ve.size() <<" capacity: " << ve.capacity() << endl;

  if(ve.empty())
  {
    cout<<"there is no elem in ve Vector"<<endl;
  }

  return 0;
  
}
