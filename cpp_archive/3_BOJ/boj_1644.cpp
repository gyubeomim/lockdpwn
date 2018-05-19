/*
  c++ ==> 백준 1644, 소수의 연속합을 푼 정답 코드

          에라토스테네스의 체로 소수뽑기 + 투포인터를 사용해서 풀었다


  code from [http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220553180497&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList]
*/
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
  int N;
  cin >> N;

  bool np[4000000] = {0};
  vector<int> prime(1, 2);  // prime.size() : 1, prime[0] : 2

  // 에라토스테네스의 체로 소수 뽑기
  for(int i=3; i<4000000; i+=2) {     // would be 3,5,7,9,11...
    if(np[i]) continue;
    prime.push_back(i);
    if(1LL*i*i >= 4000000) continue;    // would be 3^2, 5^2, 7^2, 9^2, 11^2 ...

    for(int j=i*i; j<4000000; j+=i*2) { // would be 3^2, 3^2+6, 3^2+12, 3^2+18 ...
      np[j] = true;                     //          5^2, 5^2+10, 5^2+20, 5^2+30 ...
    }
  }

  // 결과 구하기
  // 배열에서 연속한 구간의 합이 k가 되는 경우의 수를 구하기
  int result=0, sum=0, low=0, high=0;
  while(true) {
    if(sum >= N)
      sum -= prime[low++];
    else if(high == prime.size())
      break;
    else
      sum += prime[high++];

    if(sum == N)
      result++;
  }
  cout << result << endl;
  return 0;
}
