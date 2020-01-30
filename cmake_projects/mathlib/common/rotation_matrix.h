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

  /// \brief Convert Euler angle to Rotation matrix.
  /// \param[in] euler Euler angle.
  void ConvertFromEulerAngle(Eigen::Vector3d euler);

  /// \brief Convert Angle axis to Rotation matrix.
  /// \param[in] angleaxis Angle axis angle.
  void ConvertFromAngleAxis(Eigen::Vector4d angleaxis);

  /// \brief Convert Quaternion to Rotation matrix.
  /// \param[in] quaternion Quaternion.
  void ConvertFromQuaternion(Eigen::Vector4d quaternion);

 public:
  /// \brief Get rotation matrix.
  Eigen::Matrix3d R() { return R_; }

  /// \brief Set rotation matrix.
  void SetR(Eigen::Matrix3d R) { R_ = R; }
};

}  // namespace mathlib

#endif /* SO3_H */
