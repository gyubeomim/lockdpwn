/*
  c++ ==> 백준 2086, 피보나치 수의 합 문제를 푼 정답 코드

          # 1에서 N까지의 피보나치 수의 합 = N+2 번째 피보나치 수 -1
          # A-B에서 음수가 나올 수 있으므로 (A%mod - B%mod + mod)%mod 를 사용했다.

  code from [http://his130.tistory.com/145]
*/
#include <iostream>
#include <vector>

using namespace std;
const long long mod = 1000000000;
typedef vector<vector<long long>> matrix;

matrix operator*(matrix a, matrix b) {
  matrix ret(2, vector<long long>(2));

  for(int i=0; i<2; i++) {
    for(int j=0; j<2; j++) {
      long long sum=0;
      for(int m=0; m<2; m++) {
        sum += ((a[i][m]%mod) * (b[m][j]%mod)) % mod;
      }
      ret[i][j] = sum % mod;
    }
  }
  return ret;
}

matrix calc(matrix a, long long b) {
  if (b == 0) {
    matrix ret(2, vector<long long>(2));
    ret[0][0] = 1, ret[0][1] = 0, ret[1][0] = 0, ret[1][1] = 1;
    return ret;
  }
  else if(b % 2 == 0) {
    matrix temp = calc(a, b/2);
    return temp * temp;
  }
  else {
    matrix temp = calc(a, b-1);
    return a * temp;
  }
}

int main(int argc, char **argv){
  long long a,b;
  long long ans = 0;
  scanf("%lld %lld", &a, &b);

  matrix F(2, vector<long long>(2));
  F[0][0] = 1, F[0][1] = 1, F[1][0] = 1, F[1][1] = 0;

  matrix B = calc(F, b+2);
  matrix A = calc(F, (a-1) + 2);

  ans = ((B[0][1] - 1)%mod - (A[0][1] - 1)%mod + mod) % mod;
  printf("%lld\n", ans);

  return 0;
}
