/*
  c++ ==> 에라토스테네스의 체를 사용해 소수를 구한 다음 출력하는 코드
*/
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
  bool np[5000] = {0};
  vector<int> prime(1,2);

  // 에라토스테네스의 체를 사용해 소수를 구하는 코드
  for(int i=3; i<5000; i+=2) {
    if(np[i]) continue;
    prime.push_back(i);
    if(1LL*i*i >= 5000) continue;
    for(int j=i*i; j<5000; j+=i*2) {
      np[j] = 1;
    }
  }

  for(int i=0; i<=5000; i++) {
    if(prime[i] != 0) {
      cout << prime[i] << ", ";
      if(i > 9 && i%10 == 0)
        cout << endl;
    }
  }
  cout << endl;
  return 0;
}
