#include <Eigen/Core>
#include <Eigen/Dense>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

int main(int argc, char **argv) {
  std::ifstream file(std::string(getenv("HOME")) + "/catkin_ws/evaluation/200312_outdoor_stereo1/keyframe_trans.txt");

  Eigen::Vector3d prev_trans;
  Eigen::Vector3d curr_trans;
  Eigen::Vector3d diff_trans;
  double total_dist=0;

  if(file.is_open()) {
    std::string line;
    std::vector<std::string> token;
    std::vector<double> data(3);

    int i=0;
    while(!file.eof()) {
      std::getline(file, line);
      boost::split(token, line, boost::is_any_of(" "));

      data.clear();
      for(int i=0; i<token.size(); i++) {
        std::istringstream os(token.at(i));
        double r;
        os >> r;
        data.push_back(r);
      }

      // skip the invalid values.
      if(data.size() < 3) {
        continue;
      }

      if(i%2==0) {
        // read even lines.
        prev_trans << data.at(0), data.at(1), data.at(2);
      }
      else {
        // read odd lines.
        curr_trans << data.at(0), data.at(1), data.at(2);

        // get small distance.
        diff_trans = curr_trans - prev_trans;
        // accumulate it.
        total_dist += diff_trans.norm();
      }
      i += 1;
    }
  }

  std::cout << "[+] Total distance: " << total_dist << " [m]"<< std::endl;
  file.close();

  return 0;
}
