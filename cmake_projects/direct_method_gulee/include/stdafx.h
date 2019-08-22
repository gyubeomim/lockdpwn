#ifndef STDAFX_H_
#define STDAFX_H_

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/nonfree/nonfree.hpp>
// opencv 2.4.x , no opencv_contrib, extra module.
// Because no openfabmap for opencv 3.x.x
// just BUILD_opencv_nonfree module on.


#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <sophus/se3.hpp>
#include <sophus/se2.hpp>

#include <chrono>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <fstream>

#define SUPPORT_VERBOSE 1

typedef float real;

template<typename K, typename T>
using EigenMap = std::map<K, T, std::less<size_t>,
                          Eigen::aligned_allocator<std::pair<K,T> > >;

using VectorMatrixXf = std::vector<Eigen::MatrixXf, Eigen::aligned_allocator<Eigen::MatrixXf> >;
using VectorMatrixXd = std::vector<Eigen::MatrixXd, Eigen::aligned_allocator<Eigen::MatrixXd> >;

template<typename T>
using VectorMatrixX = std::vector<Eigen::Matrix<T,-1,-1>, Eigen::aligned_allocator<Eigen::Matrix<T,-1,-1> > >;

template<typename T>
using VectorVectorX = std::vector<Eigen::Matrix<T,-1,1>, Eigen::aligned_allocator<Eigen::Matrix<T,-1,1> > >;

enum TestCase
{
  FULL_OPTIMIZATION,
  BA_OPTIMIZATION,
  SE2_MARGINALIZATION,
  SE3_MARGINALIZATION,
  INVD_TEST,
  MOTION_TEST, // Rectoring direct method
};

#endif
