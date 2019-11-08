#ifndef SO3_H
#define SO3_H

#include "mathlib.h"

namespace mathlib {

class SO3{
 private:
  Eigen::Matrix3d so3_;
  Eigen::Matrix3d SO3_;

 public:
  SO3();

  SO3(Eigen::Matrix3d so3);

  ~SO3() {}

  /// \brief Get lie algebra so(3) from 3D vector.
  /// \param[in] w Input vector
  /// \return so3 element.
  Eigen::Matrix3d Compute_so3(Eigen::Vector3d w);

  /// \brief Perform exponential mapping.
  /// \param[in] so3 Lie algebra so3 element.
  /// \return SO(3) rotation matrix.
  Eigen::Matrix3d exp(Eigen::Matrix3d so3);

 public:
  Eigen::Matrix3d Getso3() { return so3_; }
  Eigen::Matrix3d GetSO3() { return SO3_; }
};

}  // namespace mathlib

#endif /* SO3_H */
