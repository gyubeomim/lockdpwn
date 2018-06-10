/*
 * #+DESCRIPTION:  백준 10825, 국영수 문제를 푼 코드
 * #+CATEGORY:
 * #+LEVEL:        -
 * #+FROM:         -
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Person {
  string name;
  int kor, eng, math;
};

int main(int argc, char **argv){
  int n;
  cin >> n;

  vector<Person> a(n);

  for (int i=0; i<n; i++) {
    cin >> a[i].name >> a[i].kor >> a[i].eng >> a[i].math;
  }

  sort(a.begin(), a.end(), [](const Person &u, const Person &v){
      if(u.kor > v.kor)
        return true;
      else if (u.kor == v.kor){
        if(u.eng < v.eng)
          return true;
        else if(u.eng == v.eng){
          if (u.math > v.math)
            return true;
          else if(u.math == v.math)
            return u.name < v.name;
        }
      }
      return false;
    });

  for (Person &p : a) {
    cout << p.name << '\n';
  }

  return 0;
}
