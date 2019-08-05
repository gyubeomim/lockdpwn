/*
  c++ stl p146 알고리즘 sort와 함수포인터를 사용해 오름차순 내림차순 구현한 코드(greater<int>, less<int>)
 */
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <stdio.h>


using namespace std;


int main()
{
  vector<int> ve;

  ve.push_back(50);
  ve.push_back(10);
  ve.push_back(20);
  ve.push_back(40);
  ve.push_back(30);

  sort(ve.begin(), ve.end(), less<int>()); // 오름차순 정렬

  for(vector<int>::iterator iter = ve.begin() ; iter != ve.end(); ++iter)
  {
    cout<< *iter << " ";
  }
  cout << endl;




  
  sort(ve.begin(), ve.end(), greater<int>());  // 내림차순 정렬
  
  for(vector<int>::iterator iter = ve.begin() ; iter != ve.end(); ++iter)
  {
    cout<< *iter << " ";
  }
  cout << endl;
  
  
  
  return 0;
  
}
