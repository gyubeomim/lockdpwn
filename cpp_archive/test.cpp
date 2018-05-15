#include <iostream>
#include <algorithm>

using namespace std;

int N,C,x[100],limit;

bool possible(int current, int remain) {
  if(remain==0) return true;

  for(int i=current+1; i<N; i++) {
    if(x[i]-x[current] >= limit)
      return possible(i, remain-1);
  }
  return false;
}

int main(int argc, char **argv) {
  cin >> N >> C;
  for(int i=0; i<N; i++) {
    cin >> *(x+i);
  }

  int upper=x[N-1]+1;
  int lower=1;
  while(lower+1 < upper) {
    limit = (lower+upper)/2;
    if(possible(0, C-1))
      lower = limit;
    else
      upper = limit;
  }
  cout << lower << endl;


  return 0;
}
