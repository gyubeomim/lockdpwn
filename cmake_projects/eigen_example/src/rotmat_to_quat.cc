#include <Eigen/Core> 
#include <Eigen/Dense>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

int main(int argc, char **argv) {
  std::ifstream file(std::string(getenv("HOME")) + "/dataset/kitti/data_odometry/poses/00.txt");

  Eigen::Matrix3d Rwc;
  Eigen::Quaterniond q;

  if(file.is_open()) {
    std::string line;
    std::vector<std::string> token;
    std::vector<double> rvec(9);

    while(!file.eof()) {
      std::getline(file, line);
      boost::split(token, line, boost::is_any_of(" "));

      rvec.clear();
      for(int i=0; i<token.size(); i++) {
        if (i==3 || i == 7 || i == 11) {
          continue;
        }
        std::istringstream os(token.at(i));
        double r;
        os >> r;
        rvec.push_back(r);
      }

      Rwc << rvec.at(0), rvec.at(1), rvec.at(2),
          rvec.at(3), rvec.at(4), rvec.at(5),
          rvec.at(6), rvec.at(7), rvec.at(8) ;

      q = Rwc;

      std::cout << "Rwc: " << Rwc << std::endl;
      std::cout << "Quat: " << q.w() << ", " << q.x() << ", " << q.y() << ", " << q.z() << std::endl << std::endl;

      Rwc = Eigen::Matrix3d();
    }
  }


  return 0;
}
