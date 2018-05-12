/*
  c++ ==> 백준 10825, 국영수 문제의 해답 코드

          도현이네 반 학생 N명의 이름과 국어, 영어, 수학 점수가 주어진다. 이 때, 다음과 같은 조건으로 학생의 성적을 정렬하는 프로그램을 작성하시오.

          국어 점수가 감소하는 순서로
          국어 점수가 같으면 영어 점수가 증가하는 순서로
          국어 점수와 영어 점수가 같으면 수학 점수가 감소하는 순서로
          모든 점수가 같으면 이름이 사전 순으로 증가하는 순서로 (단, 아스키 코드에서 대문자는 소문자보다 작으므로 사전순으로 앞에 온다.)

          code from https://www.acmicpc.net/blog/view/10
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

struct Person {
  string name;
  int kor, eng, math;
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
