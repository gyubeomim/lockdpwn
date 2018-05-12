/*
  c++ ==> 백준 10825, 국영수 문제를 푼 코드2

Input :
12
Junkyu 50 60 100
Sangkeun 80 60 50
Sunyoung 80 70 100
Soong 50 60 90
Haebin 50 60 100
Kangsoo 60 80 100
Donghyuk 80 60 100
Sei 70 70 70
Wonseob 70 70 90
Sanghyun 70 70 80
nsj 80 80 80
Taewhan 50 60 90

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
