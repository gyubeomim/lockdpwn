#ifndef ROTATION_MATRIX_H
#define ROTATION_MATRIX_H

#include "mathlib.h"

namespace mathlib {

class RotationMatrix {
 private:
  Eigen::Matrix3d R_;

 public:
  /// \brief The constructor.
  RotationMatrix();

  /// \brief The constructor.
  RotationMatrix(Eigen::Matrix3d R);

  /// \brief The destructor.
  ~RotationMatrix() {}

  void ConvertFromEulerAngle(Eigen::Vector3d euler);

  void ConvertFromFixedAngle(Eigen::Vector3d fixed);

  void ConvertFromAngleAxis(Eigen::Vector4d angleaxis);

  void ConvertFromQuaternion(Eigen::Vector4d quaternion);

 public:
  /// \brief Get rotation matrix.
  Eigen::Matrix3d GetR() { return R_; }

  /// \brief Set rotation matrix.
  void SetR(Eigen::Matrix3d R) { R_ = R; }
};

}  // namespace mathlib

#endif /* SO3_H */
