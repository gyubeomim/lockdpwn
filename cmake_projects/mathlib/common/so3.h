#ifndef SO3_H
#define SO3_H

#include "mathlib.h"

namespace mathlib {

/// \class SO3Group
class SO3Group{
 private:
  /// \brief Lie algera so3 element.
  Eigen::Matrix3d so3_;

  /// \brief Lie group SO3 element.
  Eigen::Matrix3d SO3_;

 public:
  /// \brief The constructor.
  SO3Group();

  /// \brief The constructor.
  /// \param[in] so3 Lie algebra so3 element.
  SO3Group(Eigen::Matrix3d so3);

  /// \brief The destructor.
  ~SO3Group() {}

  /// \brief Compute lie algebra so(3) from 3D vector.
  /// \param[in] w Input vector
  /// \return so3 element.
  void Compute_so3(Eigen::Vector3d w);

  /// \brief Perform exponential mapping.
  /// \param[in] so3 Lie algebra so3 element.
  /// \return SO(3) rotation matrix.
  void exp(Eigen::Matrix3d so3);

 public:
  /// \brief Get so3 element.
  Eigen::Matrix3d so3() { return so3_; }

  /// \brief Get SO3 rotation matrix.
  Eigen::Matrix3d SO3() { return SO3_; }
};

}  // namespace mathlib

#endif /* SO3_H */
