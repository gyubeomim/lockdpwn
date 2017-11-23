/*
  c++ stl p272  set ==> multiset<int>은 set<int>과 다르다는 걸 보여주는 예제 코드 (중복된 값을 입력할 수 있다)
 */
#include <iostream>
#include <set>

using namespace std;


int main()
{
  multiset<int> ms;   // multiset<int> 컨테이너는 set<int>과 다르게 중복된 원소도 입력이 가능합니다

  ms.insert(50);
  ms.insert(30);
  ms.insert(80);
  ms.insert(30);
  ms.insert(70);
  ms.insert(10);
  ms.insert(60);


  multiset<int>::iterator iter;

  for(iter = ms.begin() ; iter != ms.end() ; iter++)
  {
    cout<< *iter << ' ';
  }
  cout << endl;

  cout<< "30 원소의 개수: " << ms.count(30) << endl;  // count() 멤버함수를 사용해 원소의 갯수를 셉니다


  iter = ms.find(30);
  cout << "iter : " << *iter << endl;


  

  multiset<int>::iterator lower_iter;
  multiset<int>::iterator upper_iter;

  lower_iter = ms.lower_bound(30);
  upper_iter = ms.upper_bound(30);   // lower_bound()와 upper_bound() 멤버함수를 사용해 원소를 검색할 수 있습니다

 
  cout <<"lower: " << *lower_iter << endl;
  cout<<"upper: "<<*upper_iter << endl;



  cout<< "range[lower, upper)의 순차열: " ;

  for(iter = lower_iter ; iter != upper_iter ; iter++)
  {
    cout<< *iter << ' ';
  }
  cout << endl;
  
  return 0;
  
}


    
