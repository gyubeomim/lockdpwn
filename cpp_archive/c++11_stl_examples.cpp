//START===========================================
/*
  c++ ==> vector<char>를 sort() 함수로 정렬해 본 코드
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char **argv){
  std::vector<char> v;
  v.push_back('c');
  v.push_back('b');
  v.push_back('e');
  v.push_back('a');
  v.push_back('g');

  std::sort(v.begin(), v.end());

  for (int i=0; i<5 ; i++) {
    std::cout << v[i] << std::endl;
  }
  return 0;
}
//END=============================================

//START===========================================
/*
  c++ ==> sort() 함수를 사용해 내림차순으로 데이터를 정렬해 본 예제 코드
*/
#include <iostream>
#include <functional>
#include <algorithm>

int main(int argc, char **argv){
  int arr[5];

  arr[0] = 0;
  arr[1] = 4;
  arr[2] = 3;
  arr[3] = 1;
  arr[4] = 5;

  std::sort(arr, arr+5, std::greater<int>());

  for (int i=0 ; i<5; i++) {
    std::cout << arr[i] << std::endl;
  }

  return 0;
}
//END=============================================

//START===========================================
/*
  c++ ==> stack을 사용해 본 예제 코드
*/
#include <iostream>
#include <stdio.h>
#include <stack>

using namespace std;

int main(int argc, char **argv){
  stack<int> stack;

  stack.push(4);
  stack.push(5);
  stack.push(6);

  cout << "stack size : " << stack.size() << endl;

  cout << stack.top() << endl;  // 6
  stack.pop();

  cout << stack.top() << endl;  // 5
  stack.pop();

  cout << stack.top() << endl;  // 4
  stack.pop();

  if (stack.empty()) {
    cout << "stack is empty " << endl;
  }

  return 0;
}
//END=============================================
//START===========================================
/*
  c++ ==> c++11의 array 를 사용해 본 예제 코드
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <array>

int main(int argc, char **argv){
  std::array<int,10> c11Style = {1,4,3,123,5,2,6,62,24,1523};
  std::array<int,10> anotherC11;
  anotherC11 = c11Style;

  std::sort(c11Style.begin(), c11Style.end());

  for (auto i : c11Style) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;

  bool diff = (c11Style != anotherC11);
  return 0;
}
//END=============================================
