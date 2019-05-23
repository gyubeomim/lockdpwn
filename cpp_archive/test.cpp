










































#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main() {
  int month, day;
  cin >> month >> day;

  int sum = 0;

  switch(month) {
    case 12:
      sum += 30;
    case 11:
      sum += 31;
    case 10:
      sum += 30;
    case 9:
      sum += 31;
    case 8:
      sum += 31;
    case 7:
      sum += 30;
    case 6:
      sum += 31;
    case 5:
      sum += 30;
    case 4:
      sum += 31;
    case 3:
      sum += 28;
    case 2:
      sum += 31;
    case 1:
      sum += day;
      break;
  }

  cout << "sum: " << sum << endl;

  switch(sum%7) {
    case 0:
      cout << "SUN" << endl;
      break;
    case 1:
      cout << "MON" << endl;
      break;
    case 2:
      cout << "TUE" << endl;
      break;
    case 3:
      cout << "WED" << endl;
      break;
    case 4:
      cout << "THU" << endl;
      break;
    case 5:
      cout << "FRI" << endl;
      break;
    case 6:
      cout << "SAT" << endl;
      break;
  }

  return 0;
}
