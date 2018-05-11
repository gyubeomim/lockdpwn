//START===========================================
/*
  c ==> Fibonacci 수열을 구하는 예제코드
*/
#include <stdio.h>

int Fibonacci(int n) {
  if (n == 1)
    return 0;
  else if (n == 2)
    return 1;
  else
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main(int argc, const char *argv[]) {
  for (int i = 1; i < 15; i++) {
    printf("%d ", Fibonacci(i));
  }
  printf("\n");
  return 0;
}
//END=============================================
