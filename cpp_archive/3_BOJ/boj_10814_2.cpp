/*
 * #+DESCRIPTION:  백준 10814, 나이순 정렬 문제를 푼 정답코드, stable_sort 함수를 사용해 문제를 풀었다
 * #+CATEGORY:     sort
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 정렬
 * #+DATE:         2018-06-18-월
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct Person {
  int age;
  string name;
};

bool cmp(const Person &u, const Person &v) {
  return u.age < v.age;
}

int main() {
  int n;
  cin >> n;
  vector<Person> a(n);

  for(int i=0; i<n; i++)
    cin >> a[i].age >> a[i].name;

  // ed: stable_sort는 정렬할 때 같은 값들끼리 순서를 유지해준다
  stable_sort(a.begin(), a.end(), cmp);

  for(int i=0; i<a.size(); i++) {
    cout << a[i].age << ' ' << a[i].name;
    printf("\n");
  }
  return 0;
}
