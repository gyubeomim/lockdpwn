#include <iostream>
#include <map>

using namespace std;

int main()
{
  map<int,int> m;

  m[5] = 100;
  m[3] = 100;
  m[8] = 30;
  m[4] = 40;
  m[1] = 70;
  m[7] = 100;
  m[9] = 50;
  
  map<int,int>::iterator iter;

  for(iter = m.begin() ; iter != m.end() ; iter++)
  {
    
  }
  

  
  return 0;
}
