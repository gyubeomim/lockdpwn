// @date:              2020.08.10.Mon
// @level:             1
// @category:          Basic
// @description:       킹,퀸,룩,비숍,나이트,폰
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  cin >> N;
  cout << 1 - N << ' ';

  cin >> N;
  cout << 1 - N << ' ';

  cin >> N;
  cout << 2 - N << ' ';

  cin >> N;
  cout << 2 - N << ' ';

  cin >> N;
  cout << 2 - N << ' ';

  cin >> N;
  cout << 8 - N << endl;

  return 0;
}
