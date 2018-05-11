#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv){
  unsigned int microsec = 1500000;

  auto _start = chrono::system_clock::now();
  usleep(microsec);
  auto _end = chrono::system_clock::now();

  long millisecs = chrono::duration_cast<chrono::milliseconds>(_end - _start).count();

  cout << "It takes [" << millisecs << "] milliseconds" << endl;
  return 0;
}
