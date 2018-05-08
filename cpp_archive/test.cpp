#include <iostream>
#include <algorithm>
#include <cstring>
#include <array>

int main(int argc, char **argv){
  int oldStyle[3] = {1, 4, 3};
  int anotherOld[3];

  std::memcpy(anotherOld, oldStyle, sizeof(int)*3);
  std::sort(oldStyle, oldStyle, 3);

  for (auto i : oldStyle) {
    std::cout << i << ' ';
  }

  bool dif = false;
  for (int i=0 ; i<3 ; i) {
    if (oldStyle[i] != anotherOld[i]) {
      dif = true;
      break;
    }
  }

  std::array<int,3> c11Style = {1,4,3};
  std::array<int,3> anotherC11;

  anotherC11 = c11Style;

  for (auto i : c11Style) {
    std::cout << i << ' ';
  }

  bool diff = (c11Style != anotherC11);
  return 0;
}
