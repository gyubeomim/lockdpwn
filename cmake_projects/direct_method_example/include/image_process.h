#ifndef IMAGE_PROCESS_H_
#define IMAGE_PROCESS_H_
#include "stdafx.h"

bool scaled_warp(const std::vector<cv::Mat>& vim,
        const Eigen::Vector2f& x,
        float patch_scale,
        cv::Mat& dst);

bool scaled_warp(const std::vector<cv::Mat>& vim,
        const Eigen::Vector2f& x,
        float patch_scale,
        int lv0,
        cv::Mat& dst);

// TODO

cv::Mat pyrUpNoFilter(const cv::Mat& im);

void gradient(const cv::Mat& im,
        cv::Mat& ix,
        cv::Mat& iy);

cv::Mat sub(cv::Mat im1_32f, cv::Mat im0_32f, cv::Scalar color);

#endif
