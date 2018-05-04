/*
  c++ ==>
 */
#include <iostream>
#include <set>
#include <typeinfo>

using namespace std;

int main()
{
  set<int, less<int> > s_less;
  set<int, greater<int> > s_greater;

  s_less.insert(50);
  s_less.insert(80);
  s_less.insert(40);
  s_less.insert(5230);
  s_less.insert(180);
  s_less.insert(420);
  s_less.insert(550);
  s_less.insert(8660);
  s_less.insert(4);

  s_greater.insert(50);
  s_greater.insert(80);
  s_greater.insert(40);
  s_greater.insert(5230);
  s_greater.insert(180);
  s_greater.insert(420);
  s_greater.insert(550);
  s_greater.insert(8660);
  s_greater.insert(4);
  
  set<int, less<int> >::key_compare l_cmp = s_less.key_comp();
  cout << l_cmp(10,20) << endl;

  set<int, greater<int> >::key_compare g_cmp = s_greater.key_comp();  
  cout << g_cmp(10,20) << endl;

  cout<<"key_compare type: " << typeid(s_less.key_comp()).name() << endl;
  cout<<"key_compare type: " << typeid(s_greater.key_comp()).name() << endl;
  cout<<"value_compare type: " << typeid(s_less.value_comp()).name() << endl;
  cout<<"value_compare type: " << typeid(s_greater.value_comp()).name() << endl;
  
  return 0;
}
