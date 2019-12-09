#ifndef MATHLIB_H
#define MATHLIB_H

#include <Eigen/Dense>
#include <Eigen/Core>

#include <iostream>

#include "so3.h"
#include "rotation_matrix.h"

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

/// \brief Get rotation matrix of x axis.
/// \param[in] angle Amount of rotation.
/// \return Rotation matrix.
Eigen::Matrix3d RotateX(double angle);

/// \brief Get rotation matrix of y axis.
/// \param[in] angle Amount of rotation.
/// \return Rotation matrix.
Eigen::Matrix3d RotateY(double angle);

/// \brief Get rotation matrix of z axis.
/// \param[in] angle Amount of rotation.
/// \return Rotation matrix.
Eigen::Matrix3d RotateZ(double angle);

}// namespace mathlib
#endif /* MATHLIB_H */
