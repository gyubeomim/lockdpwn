// @date:              2020.07.30.Thu
// @level:             1
// @category:          Basic
// @description:       2693. N번째 큰 수
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    int A[10];
    memset(A, 0, sizeof(A));

    for(int i=0; i<10; i++) {
      cin >> A[i];
    }

    sort(A, A+10);
    cout << A[7] << endl;
  }

  return 0;
}
