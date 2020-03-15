#include <chrono>
#include <thread>
#include <iostream>

class TicToc{
 public:
  TicToc() {
    tic();
  }

  void tic() {
    start_ = std::chrono::system_clock::now();
  }

  double toc() {
    end_ = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end_ - start_;
    return elapsed.count() * 1000; // [ms]
  }

 private:
  std::chrono::time_point<std::chrono::system_clock> start_, end_;
};

int main() {
  TicToc t;

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  std::cout << t.toc() << std::endl;

  return 0;
}
