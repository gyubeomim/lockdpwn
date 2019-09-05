#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/xfeatures2d.hpp"

using namespace std;
using namespace cv;

int main(int argc, const char* argv[]) {
  cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
  /* cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create(); */
  /* cv::Ptr<Feature2D> f2d = ORB::create(); */

  // you get the picture, i hope..
  Mat img_1 = imread("/home/atlas1/Pictures/keep/test/1.pgm", 1);
  Mat img_2 = imread("/home/atlas1/Pictures/keep/test/2.pgm", 1);

  //-- Step 1: Detect the keypoints:
  std::vector<KeyPoint> keypoints_1, keypoints_2;    
  f2d->detect(img_1, keypoints_1);
  f2d->detect(img_2, keypoints_2);

  cv::Mat out_1, out_2;
  cv::drawKeypoints(img_1, keypoints_1, out_1);
  cv::drawKeypoints(img_2, keypoints_2, out_2);
  // cv::imwrite("sift_result1.jpg", out_1);
  // cv::imwrite("sift_result2.jpg", out_2);

  //-- Step 2: Calculate descriptors (feature vectors)    
  Mat descriptors_1, descriptors_2;    
  f2d->compute(img_1, keypoints_1, descriptors_1);
  f2d->compute(img_2, keypoints_2, descriptors_2);

  //-- Step 3: Matching descriptor vectors using BFMatcher :
  BFMatcher matcher;
  std::vector<DMatch> matches;
  matcher.match(descriptors_1, descriptors_2, matches);


  Mat img_matches;
  drawMatches(img_1, keypoints_1, img_2, keypoints_2,
               matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

  //--Step 4: Show detected (drawn) keypoints
  imshow("matching two images", img_matches);
  waitKey(0);

  return 0;
}
