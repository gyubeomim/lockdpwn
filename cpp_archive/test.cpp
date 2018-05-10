#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char **argv){
  std::vector<char> v;
  v.push_back('c');
  v.push_back('b');
  v.push_back('e');
  v.push_back('a');
  v.push_back('g');

  std::sort(v.begin(), v.end());

  for (int i=0; i<5 ; i++) {
    std::cout << v[i] << std::endl;
  }
  return 0;
}
