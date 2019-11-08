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


} // namespace mathlib
