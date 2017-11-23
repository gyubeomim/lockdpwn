/*
  c++ stl p183 vector ==> swap()을 사용해 객체의 메모리를 해제하는 예제 코드
*/

#include <iostream>
#include <vector>


using namespace std;


int main()
{
  vector<int> ve(5);
  
  cout<< "size: "<<ve.size() <<" capacity: " << ve.capacity() << endl;

  // 임시객체와 ve 벡터를 swap하면 메모리를 반환할 수 있다
  vector<int>().swap(ve);

  cout<<"[*] AFTER SWAP"<<endl;
  
  cout<< "size: "<<ve.size() <<" capacity: " << ve.capacity() << endl;


  

  return 0;
  
}
