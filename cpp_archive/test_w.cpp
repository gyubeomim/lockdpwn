#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int N,C,x[200000],limit;

bool possible(int current, int remain) {
  if(remain==0) return true;

  for(int i=current; i<N; i++){
    if(x[i]-x[current]>=limit) 
      return possible(i, remain-1);
  }
  return false;
}

int main() {
  cin >> N >> C;

  for (int i = 0; i < N; i++) {
    cin >> x[i];
  }

  sort(x, x+N);

  int lo=1;
  int hi=x[N-1]+1;

  while (lo < hi) {
      limit = (lo + hi) / 2;

      if (possible(0, C - 1)) 
        lo = limit + 1;
      else
        hi = limit;
  }
  cout << lo-1 << '\n';

  return 0;
}