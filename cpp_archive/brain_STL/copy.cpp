/*
  c++ stl p336 algo ==> copy() 알고리즘을 활용해 벡터원소를 복사하는 예제 코드
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
  vector<int> v1;

  v1.push_back(10);
  v1.push_back(20);
  v1.push_back(30);
  v1.push_back(40);
  v1.push_back(50);


  vector<int> v2(5);


  vector<int>::iterator iter;
	
	
  iter = copy(v1.begin(), v1.end(), v2.begin());



  cout << "v2 마지막 원소: " << *(iter - 1) << endl;
  cout << "v1 : ";
  for (vector<int>::size_type i = 0; i < v1.size(); i++)
  {
    cout << v1[i] << " ";
  }
  cout << endl;

	

  cout << "v2 : ";
  for (vector<int>::size_type i = 0; i < v2.size(); i++)
  {
    cout << v2[i] << " ";
  }
  cout << endl;


  return 0;
}
