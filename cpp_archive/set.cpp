/*
  c++ stl p254 set ==> set<int> 컨테이너 첫 사용 예제 코드
 */
#include <iostream>
#include <set>

using namespace std;

int main()
{
  set<int> s;

  s.insert(50);
  s.insert(30);
  s.insert(80);
  s.insert(40);
  s.insert(10);
  s.insert(70);
  s.insert(90);


  set<int>::iterator iter;

  for(iter = s.begin() ; iter != s.end(); iter++)
  {
    cout<< *iter <<endl;   // set<int> 컨테이너는 알아서 오름차순으로 원소들을 정렬합니다 : 10 30 40 50 70 80 90...
  }
  cout << endl;

  
  s.insert(50);
  s.insert(50);   // 중복값들은 허용되지 않습니다 (multiset을 사용하면 됨)

  for(iter = s.begin() ; iter != s.end(); iter++)
  {
    cout<< *iter <<endl;
  }
  cout << endl;

  s.insert(50);

  
  return 0;
}
