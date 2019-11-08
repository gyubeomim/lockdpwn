#include <Eigen/Dense>
#include <Eigen/Core>

#include <iostream>

namespace mathlib {

/// \brief Perform skew symmetric matrix.
/// \param[in] w Input 3D vector.
/// \return Skew symmetric matrix.
Eigen::Matrix3d skew(Eigen::Vector3d w);

/// \brief Perform cross product.
/// \param[in] v1 A 3D vector.
/// \param[in] v2 A 3D vector.
/// \return Cross product vector.
Eigen::Vector3d cross(Eigen::Vector3d v1, Eigen::Vector3d v2);

/// \brief Perform dot product.
/// \param[in] v a 3D vector.
/// \param[in] w a 3D vector.
/// \return Dot product scalar.
double dot(Eigen::Vector3d v, Eigen::Vector3d w);

/// \brief Get Magnitude of matrix and normalize it.
/// \param[in/out] X 3x3 matrix to be normalized.
/// \return Magnitude of the matrix.
double GetMagnitudeAndNormalize(Eigen::Matrix3d& X);


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


}// namespace mathlib
