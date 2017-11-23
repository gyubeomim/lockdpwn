#include <iostream>
#include <list>

using namespace std;

struct Greater
{
  bool operator() (int left, int right) const
  {
    return left > right;
  }
};

int main()
{
  list<int> lt;

  lt.push_back(20);
  lt.push_back(10);
  lt.push_back(50);
  lt.push_back(30);
  lt.push_back(40);
  lt.push_back(220);
  lt.push_back(1430);
  lt.push_back(520);
  lt.push_back(310);
  lt.push_back(420);
  lt.push_back(4420);
  lt.push_back(120);
  lt.push_back(530);
  lt.push_back(3);
  lt.push_back(4);

  list<int>::iterator iter;

  for(iter = lt.begin(); iter != lt.end(); iter++)
  {
    cout<< *iter<< ' ';
  }
  cout<<endl<< endl;

  lt.sort(greater<int>());
  cout<<"[AFTER greater<int>]"<<endl;
  
  for(iter = lt.begin(); iter != lt.end(); iter++)
  {
    cout<< *iter<< ' ';
  }
  cout<<endl<< endl;

  lt.sort(less<int>());
  cout<<"[AFTER less<int>]"<<endl;
  
  for(iter = lt.begin(); iter != lt.end(); iter++)
  {
    cout<< *iter<< ' ';
  }
  cout<<endl<< endl;

  lt.sort(Greater());
  cout<<"[AFTER Greater]"<<endl;
 
  for(iter = lt.begin(); iter != lt.end(); iter++)
  {
    cout<< *iter<< ' ';
  }
  cout<< endl<<endl;

  return 0;
}
