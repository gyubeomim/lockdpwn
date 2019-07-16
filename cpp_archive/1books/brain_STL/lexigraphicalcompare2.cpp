/*
  c++ stl p321 algo ==> lexicographical_compare() 알고리즘을 less<int>() , greater<int>(), Less<int>()를 활용해 사용해본 예제코드
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


template<typename T>
struct Less
{

  bool operator() (const T& left, const T& right) const
  {
    return left < right;
  }

};
// Less<int>()



int main()
{
  vector<int> v1;

  v1.push_back(10);
  v1.push_back(20);
  v1.push_back(30);

  vector<int> v2;

  v2.push_back(10);
  v2.push_back(20);
  v2.push_back(50);





  // less<int>() , greater<int>(), Less<int>() 를 활용해 두 벡터객체를 비교한다
  if(lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(),less<int>()))
  {
    cout << "less: ";
    cout << "v1 < v2" << endl;
  }
  else
  {
    cout << "less: ";
    cout << "v1 >= v2" << endl;
  }




  if(lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(),greater<int>()))
  {
    cout << "greater: ";
    cout << "v1 < v2" << endl;
  }
  else
  {
    cout << "greater: ";
    cout << "v1 >= v2" << endl;
  }



  if(lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(),Less<int>()))
  {
    cout << "Less: ";
    cout << "v1 < v2" << endl;
  }
  else
  {
    cout << "Less: ";
    cout << "v1 >= v2" << endl;
  }




  return 0;
}
