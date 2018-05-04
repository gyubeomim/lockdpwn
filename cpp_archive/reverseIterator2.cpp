/*
  c++ ==> stl p155 reverse_iterator가 실제원소가 아닌 다음 원소를 가르키는 이유
          순서를 뒤집을 때 --연산자를 안쓰고 ++연산자만으로 쉽게 구현이 가능하기 때문에 편의를 위해
*/
#include <iostream>
#include <vector>


using namespace std;


int main()
{
  vector<int> ve;

  ve.push_back(10);
  ve.push_back(20);
  ve.push_back(30);
  ve.push_back(40);
  ve.push_back(50);


  // reverse_iterator가 실제로 가르키는 값은 실제 포인터의 다음 값이다
  vector<int>::iterator normal_iter = ve.begin() + 4;
  vector<int>::reverse_iterator reverse_iter(normal_iter);

  cout << "normal: " << *normal_iter << endl;
  cout << "reverse: " << *reverse_iter << endl;
  cout << endl;




  for (vector<int>::iterator iter = ve.begin(); iter != normal_iter; ++iter)
  {
    cout << *iter << " ";
  }
  cout << endl;
	

  // --연산자가 아닌 ++연산자만으로 구현할 수 있어서 reverse_iterator는 다음 원소를 가르키게 구현되었다
  for (vector<int>::reverse_iterator riter = reverse_iter; riter != ve.rend(); ++riter)
  {
    cout << *riter << " ";
  }
  cout << endl;

}
