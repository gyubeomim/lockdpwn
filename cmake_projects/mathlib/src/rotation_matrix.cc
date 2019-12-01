#include "mathlib.h"

#include <cmath>

namespace mathlib {

  RotationMatrix::RotationMatrix() 
  : R_(Eigen::Matrix3d::Identity()) {}

  RotationMatrix::RotationMatrix(Eigen::Matrix3d R)
    :R_(R) {}

  void RotationMatrix::ConvertFromEulerAngle(Eigen::Vector3d euler) {

  }

  void RotationMatrix::ConvertFromFixedAngle(Eigen::Vector3d fixed) {

  }

  void RotationMatrix::ConvertFromAngleAxis(Eigen::Vector4d angleaxis) { 

  }

  void RotationMatrix::ConvertFromQuaternion(Eigen::Vector4d q) {
    double x = q(0);
    double y = q(1);
    double z = q(2);
    double w = q(3);

    double x2 = x*x;
    double y2 = y*y;
    double z2 = z*z;
    double w2 = w*w;

    double xy = x*y;
    double yz = y*z;
    double wy = w*y;
    double wx = w*x;
    double wz = w*z;
    double xz = x*z;
	
    R_(0,0) = x2 + y2 - z2 + w2;
    R_(0,1) = 2*xy - 2*wz;
    R_(0,2) = 2*xz + 2*wy;

    R_(1,0) = 2*xy + 2*wz;
    R_(1,1) = -x2 + y2 - z2 + w2;
    R_(1,2) = 2*yz + 2*wx;

    R_(2,0) = 2*xz - 2*wy;
    R_(2,1) = 2*yz + 2*wx;
    R_(2,2) = - x2 - y2 + z2 + w2;
  }

}  // namespace mathlib
