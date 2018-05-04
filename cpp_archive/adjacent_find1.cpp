/*
  c++ ==> stl p296 algo ==> adjacent_find() 알고리즘 사용 예제 코드
*/
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


int main()
{
  vector<int> v;

  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  v.push_back(30);
  v.push_back(40);
  v.push_back(40);
  v.push_back(50);



  for (vector<int>::size_type i = 0; i < v.size(); i++)
  {
    cout << v[i] << " ";
  }
  cout << endl;



  vector<int>::iterator iter;


  // adjacent_find 알고리즘을 사용해 다음 원소와 이전 원소가 같으면 그곳을 가르킵니다
  iter = adjacent_find(v.begin(), v.end());

  if (iter != v.end())
  {
    cout <<"["<< *iter <<"]"<< endl;
  }
	

  for (; iter != v.end(); iter++)
  {
    cout << *iter << endl;
  }
  cout << endl;

	
  return 0;
}

































