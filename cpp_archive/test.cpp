#include <iostream>
#include <algorithm>

using namespace std;

int n,c;
int main(int argc, char **argv) {
  cin >> n >> c;
  vector<int> v(n);

  for(int i=0; i<n; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  int left = 1;
  int right = v.back() + 1;
  int ans = 1;

  while(left <= right) {
    int mid = (left+right)/2;
    int cnt = 1;
    int current = 0;

    for(int i=0; i<n; i++) {
      if(v[i]-v[current] >= mid) {
        current = i;
        cnt++;
      }
    }

    if(cnt >= c) {
     if(ans < mid) {
       ans = mid;
     }
     left = mid+1;
    }
    else
      right = mid-1;
  }

  cout << ans << endl;
  return 0;
}
