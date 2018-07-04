/*
 * #+DESCRIPTION:       백준 1561, 놀이공원 문제를 푼 코드
 * #+CATEGORY:          Binary Search
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 이분탐색으로 정답찾기 part 2
 * #+DATE:              2018-06-25-월
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int time_[10000];
int child,amuse;

int main() {
  cin >> child >> amuse;

  for(int i=0; i<amuse; i++) {
    cin >> time_[i];
  }

  if(child <= amuse) {
    cout << child << '\n';
    return 0;
  }

  long long left = 0;
  long long right = 2000000000LL * 1000000LL;

  while(left <= right) {
    long long mid = (left + right)/2;  // ed: mid [분]
    long long begin, end;

    begin = end = 0;
    end = amuse;
    for(int i=0; i<amuse; i++) {
      end += mid/time_[i];         // ed: mid분에 탄 학생 수
    }

    begin = end;
    for(int i=0; i<amuse; i++) {
      if(mid % time_[i] == 0)
        begin -= 1;                // ed: mid분에 탄 학생 수2
    }
    begin += 1;

    if(child < begin)
      right = mid-1;
    else if(child > end)
      left = mid+1;
    else {                         // ed: mid분에 child 학생이 있는 경우
      for(int i=0; i<amuse; i++) {
        if(mid % time_[i] == 0) {
          if(child == begin) {
            cout << i+1 << '\n';
            return 0;
          }
          begin += 1;
        }
      }
    }
  }
  return 0;
}
