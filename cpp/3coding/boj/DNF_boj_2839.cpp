/*
  c++ ==> 백준 2839, 설탕배달
*/
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
  int num;
  cin >> num;

  if(num <= 3 || num >= 5000)
    return 0;

  int five_count = 0;
  int three_count = 0;
  int five_mod = 0;
  int three_mod = 0;

  five_count = num / 5;
  five_mod = num % 5;
  three_count = num / 3;
  three_mod = num % 3;

  cout << five_count << ", " << three_count << endl;

  // TODO(edward): make it complete

  if(num % 5 != 4)
    printf("%d\n", five_count + three_count);
  else
    printf("-1");

  return 0;
}
