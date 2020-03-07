/*
 * #+DESCRIPTION:  백준 10814, 나이순 정렬 문제를 푼 정답코드, lambda를 이용해 문제를 풀었다
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
  int join;
};

int main() {
  int n;
  cin >> n;
  vector<Person> a(n);

  for(int i=0; i<n; i++) {
    cin >> a[i].age >> a[i].name;
    a[i].join = i;
  }

  // ed: lambda 를 사용해 sort 함수에 3번째 파라미터를 작성했다
  sort(a.begin(), a.end(), [](Person u, Person v) {
      return (u.age < v.age) || (u.age == v.age && u.join < v.join);
    });

  for(int i=0; i<a.size(); i++)
    cout << a[i].age << ' ' << a[i].name << endl;
  return 0;
}
