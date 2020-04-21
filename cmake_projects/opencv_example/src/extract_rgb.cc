#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, const char* argv[]) {
  // std::string fn_img_left = std::string(getenv("HOME")) + "/dataset/kitti/data_odometry/sequences/00/image_2/000000.png";
  std::string fn_img_left = std::string(getenv("HOME")) + "/Pictures/3d_pokemon.jpg";

  cv::Mat img_left = cv::imread(fn_img_left, CV_LOAD_IMAGE_COLOR);
  cv::Mat img_left_bgr[3];

  cv::split(img_left, img_left_bgr);

  cv::imshow("0", img_left_bgr[0]);
  cv::waitKey(0);

  cv::imshow("1", img_left_bgr[1]);
  cv::waitKey(0);

  cv::imshow("2", img_left_bgr[2]);
  cv::waitKey(0);

  return 0;
}
