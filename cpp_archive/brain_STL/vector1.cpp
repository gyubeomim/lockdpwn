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



  // size_type을 이용해 i 값을 unsigned int 값으로 변경시켜준다
  for (vector<int>::size_type i = 0; i < ve.size(); ++i)
  {
    cout << ve[i] << endl;
  }
  cout << endl;

  cout << ve.size() << endl;			// size() : 원소의 개수
  cout << ve.capacity() << endl;		// capacity() : 할당된 메모리의 크기
  cout << ve.max_size() << endl;      // max_size() : 최대 저장가능한 원소의 개수

  return 0;
}
