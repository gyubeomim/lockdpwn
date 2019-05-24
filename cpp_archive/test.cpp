










































#include <iostream>
#include <fstream>
#include <random>

using namespace std;

std::default_random_engine generator;
std::uniform_real_distribution<double> uniform_dist1(0,1);
std::uniform_real_distribution<double> uniform_dist2(0,1);
std::uniform_real_distribution<double> uniform_dist3(0,1);

int main() {
  uniform_dist1 = std::uniform_real_distribution<double>(-0.5, 0.5);
  uniform_dist2 = std::uniform_real_distribution<double>(-0.5, 0.5);
  uniform_dist3 = std::uniform_real_distribution<double>(-0.174533, 0.174533);

  double var1=0, var2=0, var3=0;


  ofstream outfile;
  outfile.open("/home/dyros-vehicle/Downloads/temp.csv", std::ofstream::out | std::ofstream::app);
  for(int i=1; i<=1000; i++) {
    var3 =  3.8     + uniform_dist3(generator);
    var1 =  55.5024 + uniform_dist1(generator) * std::cos(var3);
    var2 = -12.6859 + uniform_dist2(generator) * std::sin(var3);

    outfile << var1 << "," << var2 << "," << var3 << endl;
  }

  return 0;
}
