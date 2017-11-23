/*
  c++ stl p145 알고리즘 sort에 관한 코드
 */
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  vector<int> ve;

  ve.push_back(10);
  ve.push_back(20);
  ve.push_back(30);
  ve.push_back(40);
  ve.push_back(50);

  list<int> list;

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  list.push_back(40);
  list.push_back(50);

  sort(ve.begin(), ve.end());  // 정렬 가능(vector는 임의 접근반복자)
  //  sort(list.begin(), list.end()); 에러! (list는 양방향 반복자이므로 정렬이 불가능하다고 한다)
  return 0;
}
