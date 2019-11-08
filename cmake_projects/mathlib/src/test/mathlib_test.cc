#include "mathlib.h"

int main(int argc, char **argv) {
  Eigen::Vector3d v = Eigen::Vector3d(1,2,3);
  Eigen::Vector3d w = Eigen::Vector3d(4,5,6);

  std::cout << mathlib::skew(v) << std::endl;

  std::cout << std::endl << mathlib::cross(v,w).transpose() << std::endl;

  std::cout << std::endl << mathlib::dot(v,w) << std::endl;

  Eigen::Matrix3d _so3 = mathlib::SO3::so3(w);
  std::cout << std::endl << "so3: " << std::endl << _so3 << std::endl;
  std::cout << std::endl << "SO3: " << std::endl << mathlib::SO3::exp(_so3) << std::endl;

  return 0;
}
