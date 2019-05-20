#include <iostream>
using namespace std;

void f(char c = ' ', int line = 1)
{
  for (int i =0 ; i < line; i++)
  {
    for (int j =0; j < 10; j++)
    {
      cout << c;
    }
    cout << endl;
  }
}

void fillLine(int n=25, char c='*')
{
  for (int i = 0; i < n; i++)
  {
    cout << c;
  }
  cout << endl;
}

int main(int argc, const char *argv[])
{
  f();
  f('%');
  f('@', 5);

  fillLine();

  return 0;
}













