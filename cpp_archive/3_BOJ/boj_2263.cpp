/*
 * #+DESCRIPTION:  백준 2263, 트리의 순회 문제를 푼 코드
 * #+CATEGORY:     Divide & Conquer
 * #+LEVEL:        -
 * #+FROM:         중급1 분할정복 part 2
 * #+DATE:         2018-06-23-토
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int inorder[100000];
int postorder[100000];
int position[100001];

void solve(int In_Start, int in_end, int post_start, int post_end) {
  if(in_start > in_end || post_start > post_end)
    return;

  int root = postorder[post_end];
  cout << root << " ";
  int p = position[root];
  int left = p - in_start;

  // ed: 루트 기준 왼쪽
  solve(in_start, p-1, post_start, post_start+left-1);
  // ed: 루트 기준 오른쪽
  solve(p+1, in_end, post_start+left, post_end-1);
}

int main() {
  int n;
  cin >> n;

  for(int i=0; i<n; i++) cin >> inorder[i];
  for(int i=0; i<n; i++) cin >> postorder[i];
  for(int i=0; i<n; i++) position[inorder[i]] = i;

  solve(0, n-1, 0, n-1);

  return 0;
}
