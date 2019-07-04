#include <iostream>
#include <fstream>
#include <thread>
#include <cmath>
#include <random>

using namespace std;

int main() {
  std::default_random_engine generator;
  std::uniform_real_distribution<double> uniform_dist1(-0.3, 0.3);
  std::uniform_real_distribution<double> uniform_dist2(-0.3, 0.3);
  std::uniform_real_distribution<double> uniform_dist3(-0.174533, 0.174533);

  double var1=0, var2=0, var3=0;

  ofstream outfile;
  outfile.open("random_posture.csv", std::ofstream::out | std::ofstream::app);
  for(int i=1; i<=1000; i++) {
    var3 =  3.8     + uniform_dist3(generator);
    var1 =  55.5024 + uniform_dist1(generator) * std::cos(var3);
    var2 = -12.6859 + uniform_dist2(generator) * std::sin(var3);

    outfile << var1 << "," << var2 << "," << var3 << endl;
  }

  return 0;
}
