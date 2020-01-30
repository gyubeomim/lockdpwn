#include "mathlib.h"

#include <cmath>

int main(int argc, char** argv) {
  // general operations
  Eigen::Vector3d v = Eigen::Vector3d(1, 2, 3);
  Eigen::Vector3d w = Eigen::Vector3d(4, 5, 6);

  std::cout << mathlib::skew(v) << std::endl;

  std::cout << std::endl
            << mathlib::cross(v, w).transpose() << std::endl;

  std::cout << std::endl
            << mathlib::dot(v, w) << std::endl;

  // SO3
  mathlib::SO3Group* _SO3 = new mathlib::SO3Group();

  _SO3->Compute_so3(w);

  _SO3->exp(_SO3->so3());

  std::cout << std::endl
            << "so3: " << std::endl
            << _SO3->so3() << std::endl;
  std::cout << std::endl
            << "SO3: " << std::endl
            << _SO3->SO3() << std::endl;

  std::cout << std::endl 
            << mathlib::RotateX(mathlib::deg2rad(90)) << std::endl;
  std::cout << std::endl
            << mathlib::RotateY(mathlib::deg2rad(90)) << std::endl;
  std::cout << std::endl
            << mathlib::RotateZ(mathlib::deg2rad(90)) << std::endl;

  // Rotation Matrix
  mathlib::RotationMatrix* rot = new mathlib::RotationMatrix();

  Eigen::Vector4d quat = Eigen::Vector4d(0, 0, 0, 1);
  std::cout << quat.transpose() << std::endl;

  rot->ConvertFromQuaternion(quat);

  std::cout << "Rotation Matrix: \n" << rot->R() << std::endl;

  delete _SO3;

  return 0;
}
