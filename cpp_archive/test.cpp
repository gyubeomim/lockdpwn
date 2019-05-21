






































#include <iostream>
#include <string>

using namespace std;

int main() {
  string s("I Love");
  string a;
  a = s;
  a.append(" C++");

  cout << a << endl;

  a.erase(6, 10);
  a.append(" You");

  cout << a << endl;

  int len = a.length();

  for(int i=0; i<3; i++) {
    string first = a.substr(0,1);
    string sub = a.substr(1, len-1);
    a = sub + " " + first;
    cout << a << endl;
  }

  return 0;
}
