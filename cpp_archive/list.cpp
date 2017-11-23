/*
  c++ stl p222 list ==> 리스트 컨테이너가 vector, deque에 비해 좋은점을 보여주는 예제 코드
                    ==> 노드기반이므로 insert()나 erase()에 대해 메모리 낭비가 없다 
 */
#include <iostream>
#include <list>

using namespace std;


int main()
{
  list<int> lt;

  lt.push_back(1);
  lt.push_back(20);
  lt.push_back(300);
  lt.push_back(4000);
  lt.push_back(50000);

  list<int>::iterator iter = lt.begin();
  list<int>::iterator iter2;


  
  for(iter = lt.begin() ; iter != lt.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout<<endl;


 ///////////////////////////////////////////////////////////

  iter = lt.begin();
  ++iter;
  ++iter;
  iter2 = lt.erase(iter);

  for(iter = lt.begin() ; iter != lt.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout<<endl;

  cout<<"iter2 : " << *iter2 <<endl<<endl;


 ///////////////////////////////////////////////////////////

  iter = iter2;
  iter2 = lt.insert(iter,333);

  for(iter = lt.begin() ; iter != lt.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout<<endl;

  
  cout<<"iter2 : " << *iter2 <<endl;


  return 0;
}
