/*
 * #+DESCRIPTION:  백준 1991, 트리 순회 문제를 푼 코드, 재귀함수를 사용해 preorder, inorder, postorder 를 구현했다
 * #+CATEGORY:     TREE
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 트리1 트리의 순회
 * #+DATE:         2018-06-20-수
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
using namespace std;

int a[50][2];

// ed: 전위순회
void preorder(int x) {
  if(x==-1) return;

  cout << (char)(x+'A');
  preorder(a[x][0]);
  preorder(a[x][1]);
}

// ed: 중위순회
void inorder(int x) {
  if(x==-1) return;

  inorder(a[x][0]);
  cout << (char)(x+'A');
  inorder(a[x][1]);
}

// ed: 후위순회
void postorder(int x) {
  if(x==-1) return;

  postorder(a[x][0]);
  postorder(a[x][1]);
  cout << (char)(x+'A');
}

int main() {
  int n;
  cin >> n;

  for(int i=1; i<=n; i++) {
    char x,y,z;
    cin >> x >> y >> z;
    x = x-'A';
    if(y=='.')
      a[x][0] = -1;
    else
      a[x][0] = y-'A';

    if(z=='.')
      a[x][1] = -1;
    else
      a[x][1] = z-'A';
  }

  preorder(0);
  cout << '\n';
  inorder(0);
  cout << '\n';
  postorder(0);
  cout << '\n';

  return 0;
}
