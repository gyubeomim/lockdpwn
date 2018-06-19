/*
 * #+DESCRIPTION:  백준 10825, 국영수 문제의 해답 코드, make_tuple 함수를 이용해 문제를 풀었다
 * #+CATEGORY:     sort
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 정렬
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

struct Person {
  string name;
  int kor;
  int eng;
  int math;
};

int main(int argc, char **argv) {
  int n;
  cin >> n;

  vector<Person> a(n);
  for (int i=0; i<n; i++) {
    cin >> a[i].name >> a[i].kor >> a[i].eng >> a[i].math;
  }

  sort(a.begin(), a.end(), [](const Person &u, const Person &v){
      return make_tuple(-u.kor, u.eng, -u.math, u.name) < make_tuple(-v.kor, v.eng, -v.math, v.name);
    });

  for (Person &p : a) {
    cout << p.name << '\n';
  }

  return 0;
}
