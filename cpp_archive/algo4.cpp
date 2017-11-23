/*
  c++ stl p150 vector 컨테이너를 이용한 stack 어댑터를 구현한 코드
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;


int main()
{
  stack<int , vector<int> > st;   // vector를 이용해 구현한 stack 어댑터

  // stack<int> st;
  
  st.push(10);
  st.push(20);
  st.push(30);

  cout<< st.top() << endl;
  st.pop();

  cout<< st.top()<<endl;
  st.pop();

  cout<< st.top()<<endl;
  st.pop();

  if(st.empty())
  {
    cout<< "NO DATA" <<endl;
  }

  return 0;

  
}
