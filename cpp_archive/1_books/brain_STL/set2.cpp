/*
  c++ stl p256   set ==>  insert() 멤버함수는 반환값으로 pair 객체를 반환합니다 이를 구현한 예제 코드
 */
#include <iostream>
#include <set>

using namespace std;

int main()
{
  set<int> s;
  pair<set<int>::iterator, bool> pr;    // insert() 멤버함수는 반환값으로 pair객체를 반환합니다
  // pair.first : 해당 값
  // pair.second : true or false 값 (값 입력이 성공했냐 실패했냐 플래그)

  
  pr = s.insert(50);
  s.insert(4444);
  s.insert(2222);

  
  if(true == pr.second)
  {
    cout<< *pr.first << " SUCCESS!"<<endl;
  }
  else
  {
    cout<< *pr.first << " FAIL!"<<endl;
  }

  
    
  set<int>::iterator iter;

  for(iter = s.begin() ; iter != s.end(); iter++)
  {
    cout<< *iter <<endl; 
  }
  cout << endl;

  

  pr = s.insert(5550);
  
  if(true == pr.second)
  {
    cout<< *pr.first << " SUCCESS!"<<endl;
  }
  else
  {
    cout<< *pr.first << " FAIL!"<<endl;
  }


  for(iter = s.begin() ; iter != s.end(); iter++)
  {
    cout<< *iter <<endl; 
  }
  cout << endl;


  
  
  return 0;
}
