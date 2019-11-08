#ifndef SO3_H
#define SO3_H

#include "mathlib.h"

namespace mathlib {
namespace SO3 {

/// \brief Get lie algebra so(3) from 3D vector.
/// \param[in] w Input vector
/// \return so3 element.
Eigen::Matrix3d so3(Eigen::Vector3d w);

/// \brief Perform exponential mapping.
/// \param[in] so3 Lie algebra so3 element.
/// \return SO(3) rotation matrix.
Eigen::Matrix3d exp(Eigen::Matrix3d so3);
}// namespace SO3


}  // namespace mathlib

#endif /* SO3_H */
