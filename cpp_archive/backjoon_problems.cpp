//START===========================================
/*
  c++ ==> 백준 1181번, 단어정렬 (미완성)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool cmp(const string &a, const string &b) {
  if(a.length() > b.length())
    return true;
  else
    return a > b;
}

int main(int argc, char **argv) {
  vector<string> vs;

  int numString = 0;
  /* string str; */
  /* cin >> numString; */
  /* for (int i=0; i<numString ; i++) { */
  /*   cin >> str; */
  /*   vs.push_back(str); */
  /* } */

  vs.push_back("but");
  vs.push_back("i");
  vs.push_back("wont");
  vs.push_back("hesitate");
  vs.push_back("no");
  vs.push_back("more");
  vs.push_back("no");
  vs.push_back("more");
  vs.push_back("it");
  vs.push_back("cannot");
  vs.push_back("wait");
  vs.push_back("im");
  vs.push_back("yours");

  sort(vs.begin(), vs.end(), cmp);

  for (auto i : vs) {
    std::cout << i << std::endl;
  }

  return 0;
}
//END=============================================

//START===========================================
/*
  c++ ==> 백준 2839, 설탕배달을 풀기 위한 코드 (미완성)
*/
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
  int num;
  cin >> num;

  if(num <= 3 || num >= 5000)
    return 0;

  int five_count = 0;
  int three_count = 0;
  int five_mod = 0;
  int three_mod = 0;

  five_count = num / 5;
  five_mod = num % 5;
  three_count = num / 3;
  three_mod = num % 3;

  cout << five_count << ", " << three_count << endl;

  // TODO(edward): make it complete

  if(num % 5 != 4)
    printf("%d\n", five_count + three_count);
  else
    printf("-1");

  return 0;
}
//END=============================================

//START===========================================
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
//END=============================================

//START===========================================
/*
  c++ ==> 백준 1076, 저항 문제를 푼 코드

          전자 제품에는 저항이 들어간다. 저항은 색 3개를 이용해서 그 저항이 몇 옴인지 나타낸다.
          처음 색 2개는 저항의 값이고, 마지막 색은 곱해야 하는 값이다.
          첫째 줄에 입력을 주어진 저항의 저항값을 출력한다.

          Input  : yello violet red
          Output : 4700
*/
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char **argv) {
  map<string, int> d = {
    {"black", 0}, {"brown", 1}, {"red", 2},
    {"orange", 3}, {"yellow", 4}, {"green", 5},
    {"blue", 6}, {"violet", 7}, {"grey", 8},
    {"white", 9}
  };

  string a,b,c;
  cin >> a >> b >> c;

  // ed: yellow violet red 입력을 처리하는 코드
  long long ans = (long long)(d[a]*10 + d[b]);
  for (int k=0; k<d[c]; k++) {
    ans *= 10LL;
  }

  cout << ans << '\n';
  return 0;
}
//END=============================================

//START===========================================
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
//END=============================================

//START===========================================
/*
  c++ ==> lambda로 사칙연산을 해본 예제 코드

  code from https://www.acmicpc.net/blog/view/10
*/
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    int a,b;
    cout << "Input : ";
    cin >> a >> b;

    vector<function<int(int,int)>> d;

    d.push_back([](int x, int y){
            return x+y;
        });
    d.push_back([](int x, int y){
            return x-y;
        });
    d.push_back([](int x, int y){
            return x*y;
        });
    d.push_back([](int x, int y){
            return x/y;
        });

    for(auto &f : d){
        cout << f(a,b) << '\n';
    }

    return 0;
}
//END=============================================
