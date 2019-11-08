#include "mathlib.h"

int main(int argc, char **argv) {
  Eigen::Vector3d v = Eigen::Vector3d(1,2,3);
  Eigen::Vector3d w = Eigen::Vector3d(4,5,6);

  std::cout << mathlib::skew(v) << std::endl;

  std::cout << std::endl << mathlib::cross(v,w).transpose() << std::endl;

  std::cout << std::endl << mathlib::dot(v,w) << std::endl;

  mathlib::SO3* _SO3 = new mathlib::SO3();

  _SO3->Compute_so3(w);

  _SO3->exp(_SO3->Getso3());

  std::cout << std::endl << "so3: " << std::endl << _SO3->Getso3() << std::endl;
  std::cout << std::endl << "SO3: " << std::endl << _SO3->GetSO3() << std::endl;

  delete _SO3;

  return 0;
}
