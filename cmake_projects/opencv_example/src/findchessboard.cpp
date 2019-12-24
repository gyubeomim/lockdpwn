// reference: https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#bool%20findChessboardCorners(InputArray%20image,%20Size%20patternSize,%20OutputArray%20corners,%20int%20flags)

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#define RECTIFICATION false

// reference: https://www.learnopencv.com/rotation-matrix-to-euler-angles/
// checks if a matrix is a valid rotation matrix.
bool IsRotMat(cv::Mat &R) {
  cv::Mat Rt;
  transpose(R, Rt);
  cv::Mat shouldBeIdentity = Rt * R;
  cv::Mat I = cv::Mat::eye(3,3, shouldBeIdentity.type());

  return norm(I, shouldBeIdentity) < 1e-6;
}

// calculates rotation matrix to euler angles.
cv::Vec3f RotMatToEuler(cv::Mat &R) {
  assert(IsRotMat(R));
  float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );
  bool singular = sy < 1e-6; // If
  float x, y, z;

  if (!singular) {
    x = atan2(R.at<double>(2,1) , R.at<double>(2,2));
    y = atan2(-R.at<double>(2,0), sy);
    z = atan2(R.at<double>(1,0), R.at<double>(0,0));
  }
  else {
    x = atan2(-R.at<double>(1,2), R.at<double>(1,1));
    y = atan2(-R.at<double>(2,0), sy);
    z = 0;
  }

  return cv::Vec3f(x, y, z);
}

std::string to_zero_lead(const int value, const unsigned precision) {
  std::ostringstream oss;
  oss << std::setw(precision) << std::setfill('0') << value;
  return oss.str();
}

int main(int argc, char **argv) {
#if RECTIFICATION
  std::cout << "[+] RECTIFICATION ON" << std::endl;
#else
  std::cout << "[+] RECTIFICATION OFF" << std::endl;
#endif
  for(int k=0; k < 600; k+=1) {
    std::string fn_chessboard = std::string(getenv("HOME")) +"/Pictures/keep/camera_left/" + to_zero_lead(k, 6) + ".png";
    cv::Mat image_raw = cv::imread(fn_chessboard, cv::IMREAD_GRAYSCALE);
    cv::Mat image_rect;

    /// original K matrix
    cv::Mat K = (cv::Mat_<double>(3,3) <<
                 723.752, 0, 696.227,
                 0, 724.234, 524.314,
                 0,0,1);

    /// new K matrix
    cv::Mat newK = (cv::Mat_<double>(3,3) <<
                    713.301, 0, 677.471,
                    0, 713.301, 513.183,
                    0,0,1);

    cv::Mat d = (cv::Mat_<double>(5,1) << -0.155860, 0.04628, -0.002083, -0.004656, 0.0 );

    cv::Mat R = (cv::Mat_<double>(3,3) <<
                 0.9994, 0.00938, 0.03179,
                 -0.0087, 0.9997, -0.01887,
                 -0.0319, 0.01858, 0.9993);

#if RECTIFICATION
    cv::Mat map1a, map1b;
    cv::Size image_size(1384, 1024);
    cv::initUndistortRectifyMap(K, d, R, newK, image_size, CV_32FC1, map1a, map1b);

    cv::Mat undist_left, undist_right;
    cv::remap(image_raw, image_rect, map1a, map1b, cv::INTER_LINEAR);

    image_rect.copyTo(image_raw);
#endif

    cv::Size patternsize(8,6);
    std::vector<cv::Point2f> imagepoints;

    // find imagepoints in checssboard.
    bool patternfound = cv::findChessboardCorners(image_raw, patternsize, imagepoints,
                                                  cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

    if(patternfound) {
      // refine the corner locations.
      cv::cornerSubPix(image_raw, imagepoints, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
    }

    std::vector<cv::Point3f> objectpoints;

    // add object points.
    for(int col=0; col<6; col++) {
      for(int row=0; row<8; row++) {
        cv::Point3f objpoint(0.108*col, 0.108*row, 0);
        objectpoints.push_back(objpoint);
        // // debugging (comment out).
        // std::cout << "objpoint: " << objpoint << std::endl;
      }
    }

    for(size_t i=0; i<imagepoints.size(); i++) {
      cv::Point2f ipt = imagepoints.at(i);
      cv::Point3f opt = objectpoints.at(i);

      std::cout << i << ", " << ipt << ", " << opt << std::endl;
    }

    cv::Mat angleaxis, tvec, rotmat, tvec_new;
    cv::Vec3f euler;

    cv::solvePnPRansac(objectpoints, imagepoints, K, d, angleaxis, tvec);

    // convert angle axis to rotation matrix.
    cv::Rodrigues(angleaxis, rotmat);

    // conver rotation matrix to euler angles.
    euler = RotMatToEuler(rotmat);
    euler *= 180/3.14159;

    cv::Ptr<cv::Formatter> round = cv::Formatter::get(cv::Formatter::FMT_DEFAULT);
    round->set64fPrecision(3);
    round->set32fPrecision(3);

    std::cout << std::endl << "[+] IMAGE " << to_zero_lead(k,6) << std::endl;
    // for debug (comment out).
    // std::cout << "R(angle axis): " << std::endl << round->format(angleaxis.t()) << std::endl;
    std::cout << std::endl << "R(rotation matrix): " << std::endl << round->format(rotmat) << std::endl;
    std::cout << "R(euler angle):   " <<  std::setprecision(3) << "[" << euler.val[0] << ", " << euler.val[1] << ", " << euler.val[2] << "]" << std::endl;
    // std::cout << "Translate(x,y,z): " << round->format(tvec.t()) << std::endl;

    tvec_new = -rotmat.t() * tvec;
    std::cout << "Translate(x,y,z): " << round->format(tvec_new.t()) << std::endl;

    // draw result.
    cv::Mat result = image_raw.clone();
    cv::cvtColor(result, result, cv::COLOR_GRAY2BGR);
    cv::drawChessboardCorners(result, patternsize, cv::Mat(imagepoints), patternfound);

    // draw center point.
    cv::circle(result, cv::Point(result.cols/2, result.rows/2), 10, cv::Scalar(0,0,255), -1);

    cv::imshow("cb_rect", result);
    cv::waitKey(0);
  }

  return 0;
}
