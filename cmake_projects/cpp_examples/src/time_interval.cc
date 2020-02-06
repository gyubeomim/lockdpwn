#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
  auto start = std::chrono::steady_clock::now();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  auto end = std::chrono::steady_clock::now();
  double gap = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  std::cout << "GAP " << gap << std::endl;

  return 0;
}
