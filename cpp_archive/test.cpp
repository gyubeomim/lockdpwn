#include <iostream>
#include <algorithm>
#include <cstring>
#include <array>

int main(int argc, char **argv){
  std::array<int,10> c11Style = {1,4,3,123,5,2,6,62,24,1523};
  std::array<int,10> anotherC11;
  anotherC11 = c11Style;

  std::sort(c11Style.begin(), c11Style.end());

  for (auto i : c11Style) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;

  bool diff = (c11Style != anotherC11);
  return 0;
}
