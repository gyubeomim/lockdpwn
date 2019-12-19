#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ximgproc.hpp>

#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string left_im = "/home/edward/Pictures/left.jpg";
  std::string right_im = "/home/edward/Pictures/right.jpg";

  cv::Mat left = cv::imread(left_im, cv::IMREAD_COLOR);
  cv::Mat right = cv::imread(right_im, cv::IMREAD_COLOR);
  cv::Mat left_for_matcher, right_for_matcher;

  cv::Ptr<cv::ximgproc::DisparityWLSFilter> wls_filter;

  if(left.empty()) {
    std::cout << "cannot read left image file." << std::endl;
    return -1;
  }

  if(right.empty()) {
    std::cout << "cannot read right image file." << std::endl;
    return -1;
  }

  int max_disp = 160; // default parameter.
  max_disp /= 2;
  if(max_disp % 16 != 0) {
    max_disp += 16 - (max_disp % 16);
  }

  // resize image to half size.
  double size = 1.0;
  cv::resize(left, left_for_matcher, cv::Size(), 1.0, 1.0);
  cv::resize(right, right_for_matcher, cv::Size(), 1.0, 1.0);

  int wsize = 7; // default size for StereoBM.

  cv::Ptr<cv::StereoBM> left_matcher = cv::StereoBM::create(max_disp, wsize);
  wls_filter = cv::ximgproc::createDisparityWLSFilter(left_matcher);
  cv::Ptr<cv::StereoMatcher> right_matcher = cv::ximgproc::createRightMatcher(left_matcher);

 cv::cvtColor(left_for_matcher, left_for_matcher, cv::COLOR_RGB2GRAY);
  cv::cvtColor(right_for_matcher, right_for_matcher, cv::COLOR_RGB2GRAY);

  cv::Mat left_disp, right_disp;
  cv::Mat filtered_disp, solved_disp, solved_filtered_disp;

  left_matcher->compute(left_for_matcher, right_for_matcher, left_disp);
  right_matcher->compute(right_for_matcher, right_for_matcher, right_disp);

  cv::Mat raw_disp_vis;
  double vis_mult = 1.0; // default parameter.
  cv::ximgproc::getDisparityVis(left_disp, raw_disp_vis, vis_mult);

  cv::imshow("raw disparity", raw_disp_vis);
  cv::waitKey(0);

  return 0;
}
