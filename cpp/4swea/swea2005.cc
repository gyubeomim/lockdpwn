#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  int T;
  cin >> T;

  for(int t=1; t<=T; t++) {
    int num;
    cin >> num;

    cout << '#' << t << '\n';
    cout << 1 << '\n';

    int pascal[10][10];
    for(int i=1; i<num; i++) {
      for(int j=0; j<=i; j++) {
        if(j==0 || j==i) {
          pascal[i][j] = 1;
        }
        else {
          pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
        }
      }

      for(int j=0; j<=i; j++) {
        cout << pascal[i][j] << ' ';
      }
      cout << '\n';
    }

  }

  return 0;
}
