#include <iostream>

using namespace std;

template <class T>
bool equalArray(T x[], T y[], int size){
  for (int i = 0; i < size; i++) {
    if (x[i] != y[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  int x[] = { 1, 10, 100, 5, 4 };
  int y[] = { 1, 10, 100, 5, 4 };
  double a[] = { 0.1, 2.3, 3.5 };
  double b[] = { 5.3, -2.1, 12.5 };

  if (equalArray(x, y, 5)) {
    cout << "EQUAL" << endl;
  }
  else {
    cout << "NOT EQUAL!" << endl;
  }

  if (equalArray(a, b, 3)) {
    cout << "EQUAL2" << endl;
  }
  else {
    cout << "NOT EQUAL2!" << endl;
  }
}
