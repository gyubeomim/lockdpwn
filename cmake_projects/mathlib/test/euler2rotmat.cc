// This test code convert Euler angle to Rotation Matrix.
#include "mathlib.h"

#include <cmath>

int main(int argc, char** argv) {
  // Euler angle(XYZ) in radian.
  Eigen::Vector3d euler1 = Eigen::Vector3d(3.14, 0, 0);
  Eigen::Vector3d euler2 = Eigen::Vector3d(0, 3.14, 0);
  Eigen::Vector3d euler3 = Eigen::Vector3d(0, 0, 3.14);

  mathlib::RotationMatrix* rot = new mathlib::RotationMatrix();
  rot->ConvertFromEulerAngle(euler1);
  std::cout << rot->R() << std::endl << std::endl;
  rot->ConvertFromEulerAngle(euler2);
  std::cout << rot->R() << std::endl << std::endl;
  rot->ConvertFromEulerAngle(euler3);
  std::cout << rot->R() << std::endl << std::endl;

  delete rot;
}
