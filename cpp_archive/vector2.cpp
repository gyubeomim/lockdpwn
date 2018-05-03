/*
  c++ stl p178 vector 생성자에 어떤 값을 넣느냐에 따라 다른 벡터가 생성된다 v1(5), v2(5,10)...
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> v1(5);
  vector<int> v2(5,0);   // vector 생성자에 초기값을 설정할 수 있다
  vector<int> v3(5,55555);

  for (vector<int>::size_type i = 0; i < v1.size(); ++i)
    cout << v1[i] << " ";

  cout << endl;

  for (vector<int>::size_type i = 0; i < v2.size(); ++i)
    cout << v2[i] << " ";

  cout << endl;

  for (vector<int>::size_type i = 0; i < v3.size(); ++i)
    cout << v3[i] << " ";

  cout << endl;

  return 0;
}
