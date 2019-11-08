#include "mathlib.h"

namespace mathlib {

SO3::SO3()
{}

SO3::SO3(Eigen::Matrix3d so3) {
  exp(so3);
}

Eigen::Matrix3d SO3::Compute_so3(Eigen::Vector3d w) {
  so3_ =  skew(w);
}

// https://en.wikipedia.org/wiki/3D_rotation_group
Eigen::Matrix3d SO3::exp(Eigen::Matrix3d so3) {
  double theta = GetMagnitudeAndNormalize(so3);

  double s = std::sin(theta);
  double c = std::cos(theta);

  double s2 = std::sin(theta)*std::sin(theta);
  double c2 = std::cos(theta)*std::cos(theta);

  double x = so3(2,1);
  double y = so3(0,2);
  double z = so3(1,0);

  double x2 = x*x;
  double y2 = y*y;
  double z2 = z*z;

  SO3_(0,0) = 2*(x2-1) * s2 + 1;
  SO3_(0,1) = 2*x*y*s2 - 2*z*c*s;
  SO3_(0,2) = 2*x*z*s2 + 2*y*c*s;

  SO3_(1,0) = 2*x*y*s2 + 2*z*c*s;
  SO3_(1,1) = 2*(y2-1)*s2 + 1;
  SO3_(1,2) = 2*y*z*s2 - 2*x*c*s;

  SO3_(2,0) = 2*x*z*s2 - 2*y*c*s;
  SO3_(2,1) = 2*y*z*s2 + 2*x*c*s;
  SO3_(2,2) = 2*(z2-1)*s2 + 1;
}

}  // namespace mathlib
