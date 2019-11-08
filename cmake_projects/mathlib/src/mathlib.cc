#include "mathlib.h"

namespace mathlib {

Eigen::Matrix3d skew(Eigen::Vector3d w) {
  Eigen::Matrix3d result;

  result(0,0) = 0;
  result(1,1) = 0;
  result(2,2) = 0;

  result(0,1) = -w(2);
  result(0,2) = w(1);
  result(1,0) = w(2);
  result(1,2) = -w(0);
  result(2,0) = -w(1);
  result(2,1) = w(0);

  return result;
}

Eigen::Vector3d cross(Eigen::Vector3d v, Eigen::Vector3d w) {
  Eigen::Vector3d result;

  result(0) = v(1)*w(2) - v(2)*w(1);
  result(1) = v(2)*w(0) - v(0)*w(2);
  result(2) = v(0)*w(1) - v(1)*w(0);

  return result;
}

double dot(Eigen::Vector3d v, Eigen::Vector3d w) {
  double result;

  result = v(0)*w(0) + v(1)*w(1) + v(2)*w(2);

  return result;
}

double GetMagnitudeAndNormalize(Eigen::Matrix3d& X) {
  double magnitude = X.norm();

  X /= X.norm();

  return magnitude;
}

namespace SO3 {
Eigen::Matrix3d so3(Eigen::Vector3d w) {
  return skew(w);
}

// https://en.wikipedia.org/wiki/3D_rotation_group
Eigen::Matrix3d exp(Eigen::Matrix3d so3) {
  Eigen::Matrix3d SO3;

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

  SO3(0,0) = 2*(x2-1) * s2 + 1;
  SO3(0,1) = 2*x*y*s2 - 2*z*c*s;
  SO3(0,2) = 2*x*z*s2 + 2*y*c*s;

  SO3(1,0) = 2*x*y*s2 + 2*z*c*s;
  SO3(1,1) = 2*(y2-1)*s2 + 1;
  SO3(1,2) = 2*y*z*s2 - 2*x*c*s;

  SO3(2,0) = 2*x*z*s2 - 2*y*c*s;
  SO3(2,1) = 2*y*z*s2 + 2*x*c*s;
  SO3(2,2) = 2*(z2-1)*s2 + 1;

  return SO3;
}
}  // namespace SO3


} // namespace mathlib
