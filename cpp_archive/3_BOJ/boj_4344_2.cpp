/*
  c++ ==> 백준 4344, 평균은 넘겠지 문제를 다차원 배열 동적할당으로 푼 코드

*/
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
  int C;
  cin >> C;

  int** x = new int*[C];
  for(int i=0; i<C; i++) {
    x[i] = new int[1000];
  }

  int* N = new int[C];

  for(int i=0; i<C; i++) {
    cin >> *(N+i);
    for(int j=0; j<*(N+i); j++) {
      cin >> x[i][j];
    }
  }

  double sum = 0;
  double average = 0;
  double uppercount = 0;

  for(int i=0; i<C; i++) {
    sum = 0;
    uppercount =0;
    for(int j=0; j<*(N+i); j++) {
      sum += x[i][j];
    }
    average = sum / *(N+i);
    for(int j=0; j<*(N+i); j++) {
      if(x[i][j] > average) {
        uppercount++;
      }
    }
    /* cout << uppercount / *(N+i)*100<< "%" << setprecision(5) << endl; */
    printf("%.3lf%%\n", uppercount / *(N+i)*100.0);
  }

  return 0;
}
