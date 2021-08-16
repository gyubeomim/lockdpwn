// @date:              2020.07.30.Thu
// @level:             1
// @category:          Sort
// @description:       2751. 수 정렬하기 2
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  cin >> N;

  int A[1000001];
  for(int i=0; i<N; i++) {
    scanf("%d", &A[i]);
  }

  sort(A, A+N);

  for(int i=0; i<N; i++) {
    printf("%d\n", A[i]);
  }

  return 0;
}
