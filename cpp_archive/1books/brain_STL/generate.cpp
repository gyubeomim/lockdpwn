/*
  c++ stl p346 algo ==> generate() 알고리즘을 처음 사용해본 예제 코드
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Integer {
  int data;

 public:
  explicit Integer(int d = 0) : data(d)
  {}

  int operator()() {
    return data++;
  }
};

int main() {
  vector<int> v;

  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  v.push_back(40);
  v.push_back(50);

  cout << "v : ";
  for (vector<int>::size_type i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;

  // generate() 알고리즘을 사용해서 기존 벡터객체에 +1, +100, +123을 시킵니다
  generate(v.begin(), v.end(), Integer(1));

  cout << "v : ";
  for (vector<int>::size_type i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
	
  generate(v.begin(), v.end(), Integer(100));

  cout << "v : ";
  for (vector<int>::size_type i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;


  // generate_n() 알고리즘의 사용 예제 코드.
  // generate(v.begin(), v.begin() + 3 ,Integer(123)); 과 같은 내용입니다
  generate_n(v.begin(),  3, Integer(123));

  cout << "v : ";
  for (vector<int>::size_type i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;

  return 0;
}
