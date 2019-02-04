/*
 * #+DESCRIPTION: harris corner detection example
 * #+FROM:        https://docs.opencv.org/3.4.0/d4/d7d/tutorial_harris_detector.html
 * #+DATE:        2018-07-05-목
 * #+AUTHOR:      Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;
const char* source_window = "Source image";
const char* corners_window = "Corners detected";
void cornerHarris_demo( int, void* );

int main( int argc, char** argv ) {
  CommandLineParser parser( argc, argv, "{@input | ../data/building.jpg | input image}" );
  src = imread( parser.get<String>( "@input" ), IMREAD_COLOR );

  if ( src.empty() ) {
    cout << "Could not open or find the image!\n" << endl;
    cout << "Usage: " << argv[0] << " <Input image>" << endl;
    return -1;
  }

  cvtColor( src, src_gray, COLOR_BGR2GRAY );

  namedWindow( source_window, WINDOW_AUTOSIZE );
  createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);

  imshow( source_window, src );

  cornerHarris_demo( 0, 0 );

  waitKey(0);
  return(0);
}

void cornerHarris_demo( int, void* ) {
  Mat dst, dst_norm, dst_norm_scaled;
  dst = Mat::zeros( src.size(), CV_32FC1 );

  int blockSize = 7;
  int apertureSize = 5;
  double k = 0.03;

  cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );

  for( int j = 0; j < dst_norm.rows ; j++ ) {
    for( int i = 0; i < dst_norm.cols; i++ ) {
      if( (int) dst_norm.at<float>(j,i) > thresh ) {
        circle( dst_norm_scaled, Point( i, j ), 2,  Scalar(0), 2, 8, 0 );
      }
    }
  }

  namedWindow( corners_window, WINDOW_AUTOSIZE );
  imshow( corners_window, dst_norm_scaled);
}
