/*
 * #+DESCRIPTION:  백준 1517, 버블소트 문제를 푼 코드
 * #+CATEGORY:     Divide & Conquer
 * #+LEVEL:        -
 * #+FROM:         중급1 분할정복 part 2
 * #+DATE:         2018-06-23-토
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int a[500000];
int b[500000];

long long solve(int start, int end) {
  if(start == end )
    return 0;

  int mid = (start+end) / 2;
  long long ans = solve(start, mid) + solve(mid+1, end);
  int i = start;
  int j = mid+1;
  int k = 0;

  while(i <= mid || j <= end) {
    if(i <= mid && (j > end || a[i] <= a[j]))
      b[k++] = a[i++];
    else {  // ed: Merge Sort 과정에서 오른쪽에 있는게 이동할 때 정답에 왼쪽 배열의 크기를 더해준다
      ans += (long long)(mid-i+1);
      b[k++] = a[j++];
    }
  }

  for(int i=start; i<=end; i++) {
    a[i] = b[i-start];
  }

  return ans;
}

int main() {
  int n;
  cin >> n;

  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  long long ans = solve(0, n-1);
  cout << ans << '\n';

  return 0;
}
