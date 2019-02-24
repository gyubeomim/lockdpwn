#include <Eigen/Geometry>
#include <iostream>

#define DEG2RAD M_PI/180.0

int main()
{
  Eigen::Isometry3d original = Eigen::Isometry3d::Identity();
  original.translate(1.414214*Eigen::Vector3d::UnitY());
  original.rotate(Eigen::AngleAxisd(45.0*DEG2RAD, Eigen::Vector3d::UnitZ()));

  std::cout << "original:\n" << original.matrix() << "\n" << std::endl;

  Eigen::Isometry3d cycle1 = Eigen::Isometry3d::Identity();
  cycle1.translate(1.414214*Eigen::Vector3d::UnitY());
  cycle1.rotate(Eigen::AngleAxisd(90*DEG2RAD, Eigen::Vector3d::UnitX()));
  cycle1.rotate(Eigen::AngleAxisd(45.0*DEG2RAD, Eigen::Vector3d::UnitY()));

  std::cout << "cycle 1:\n" << cycle1.matrix() << "\n" << std::endl;

  Eigen::Isometry3d diff_front = cycle1 * original.inverse();
  std::cout << "diff_front:\n" << diff_front.matrix() << "\n" << std::endl;

  Eigen::Isometry3d diff_back = original.inverse() * cycle1;
  std::cout << "diff_back:\n" << diff_back.matrix() << "\n" << std::endl;

  Eigen::Isometry3d x_90 = Eigen::Isometry3d::Identity();
  x_90.rotate(Eigen::AngleAxisd(90.0*DEG2RAD, Eigen::Vector3d::UnitX()));
  std::cout << "x_90:\n" << x_90.matrix() << "\n" << std::endl;
}
