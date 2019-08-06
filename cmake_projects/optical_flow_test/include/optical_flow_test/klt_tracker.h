#include <stdio.h>
#include <queue>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include <sensor_msgs/Image.h>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>

using namespace std;
using namespace Eigen;

void reduceVector(vector<cv::Point2f> &v, vector<uchar> status);
void reduceVector(vector<int> &v, vector<uchar> status);


class Tracker
{
public:
    Tracker();

    void trackImage(double _cur_time, const cv::Mat &_img, const cv::Mat &_img1 = cv::Mat());

    void drawTrack(const cv::Mat &imLeft, const cv::Mat &imRight, 
                               vector<int> &curLeftIds,
                               vector<cv::Point2f> &curLeftPts, 
                               map<int, cv::Point2f> &prevLeftPtsMap);
    cv::Mat getTrackImage();
    bool inBorder(const cv::Point2f &pt);

public:
    int row, col;
    cv::Mat imTrack;
    cv::Mat prev_img, cur_img;

    vector<cv::Point2f> n_pts;
    vector<cv::Point2f> prev_pts, cur_pts, cur_right_pts;

    vector<int> ids, ids_right;
    vector<int> track_cnt;

    map<int, cv::Point2f> prevLeftPtsMap;

    double prev_time, cur_time;

    int n_id;

    bool b_init;

    int MAX_CNT;
    int MIN_DIST;

    int SHOW_TRACK;
};