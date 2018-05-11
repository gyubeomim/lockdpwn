/*
  c++ stl p228 list ==> splice() 멤버함수를 통해 원소를 다른 객체로 옮기는 예제 코드
 */
#include <iostream>
#include <list>

using namespace std;

bool Predicate(int n)
{
  return 10 <= n && n <= 30;
}


int main()
{
  list<int> lt;
  list<int> lt2;

  
  lt.push_back(10);
  lt.push_back(20);
  lt.push_back(30);
  lt.push_back(40);
  lt.push_back(50);

  lt2.push_back(111);
  lt2.push_back(222);
  lt2.push_back(333);
  lt2.push_back(444);
  lt2.push_back(555);



  
  list<int>::iterator iter;

  cout<<"lt: " ;
   
  for(iter = lt.begin(); iter != lt.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout << endl;


  cout<<"lt2: " ;
   
  for(iter = lt2.begin(); iter != lt2.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout<<"=====================================" << endl;


  
  iter = lt.begin();
  ++iter;
  ++iter;
  lt.splice(iter,lt2);    // splice() 멤버함수를 통해 lt2의 모든 원소를 lt로 옮깁니다


  
  cout<<"lt: " ;
   
  for(iter = lt.begin(); iter != lt.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout << endl;


  cout<<"lt2: " ;
   
  for(iter = lt2.begin(); iter != lt2.end() ; iter++)
  {
    cout<< *iter <<endl;
  }
  cout << endl;

  


  return 0;
}
