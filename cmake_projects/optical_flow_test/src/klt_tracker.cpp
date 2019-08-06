
#include "klt_tracker.h"


bool Tracker::inBorder(const cv::Point2f &pt)
{
    const int BORDER_SIZE = 1;
    int img_x = cvRound(pt.x);
    int img_y = cvRound(pt.y);
    return BORDER_SIZE <= img_x && img_x < col - BORDER_SIZE && BORDER_SIZE <= img_y && img_y < row - BORDER_SIZE;
}

void reduceVector(vector<cv::Point2f> &v, vector<uchar> status)
{
    int j = 0;
    for (int i = 0; i < int(v.size()); i++)
        if (status[i])
            v[j++] = v[i];
    v.resize(j);
}

void reduceVector(vector<int> &v, vector<uchar> status)
{
    int j = 0;
    for (int i = 0; i < int(v.size()); i++)
        if (status[i])
            v[j++] = v[i];
    v.resize(j);
}

Tracker::Tracker()
{
    b_init = true;
    n_id = 0;

    SHOW_TRACK = true;
    MAX_CNT = 150;
    MIN_DIST = 30;
}

void Tracker::trackImage(double _cur_time, const cv::Mat &_img, const cv::Mat &_img1)
{
    _img.copyTo(cur_img);
    cv::Mat rightImg;
    _img1.copyTo(rightImg);
    // cvtColor(cur_img, cur_img, COLOR_RGB2GRAY);

    /*------ step 1 : track pts if prev_pts exists -------*/
    // if(b_init)
    // {
    //     cv::goodFeaturesToTrack(cur_img, cur_pts, MAX_CNT, 0.01, 10, cv::Mat());
    //     cv::cornerSubPix(cur_img, cur_pts, cv::Size(10,10), cv::Size(-1,-1), cv::TermCriteria(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03));
    //     b_init = false;
    // }
    // else 
    cur_pts.clear();

    if( !prev_pts.empty() )
    {
        // ROS_INFO("prev_pts size=%d",prev_pts.size());
        vector<uchar> status, statusRightLeft;
        vector<float> err;

        if(prev_img.empty())
            cur_img.copyTo(prev_img);
        cv::calcOpticalFlowPyrLK(prev_img, cur_img, prev_pts, cur_pts, status, err, cv::Size(31, 31), 3);
   
        int count_status = 0;
        for (int i = 0; i < int(cur_pts.size()); i++){
            // if (status[i] && !inBorder(cur_pts[i]))
            //     status[i] = 0;
            if(status[i])
                count_status++;
        }
        // ROS_INFO("cur_pts size=%d -> count_status=%d",cur_pts.size(), count_status);

        reduceVector(prev_pts, status);
        reduceVector(cur_pts, status);
        reduceVector(track_cnt, status);
        reduceVector(ids, status);
    }
    
    // ROS_INFO("cur_pts size=%d",cur_pts.size());
    /*------ step 2 : add pts to keep the number of pts to track  -------*/
    int n_max_cnt = MAX_CNT - static_cast<int>(cur_pts.size());
    if (n_max_cnt > 0)
    {
        cv::goodFeaturesToTrack(cur_img, n_pts, n_max_cnt, 0.01, MIN_DIST);
    }
    else
        n_pts.clear();
    
    for (auto &p : n_pts)
    {
        cur_pts.push_back(p);
        ids.push_back(n_id++);
        track_cnt.push_back(1);
    }

    /*------ step 3 : draw image  -------*/
    if(SHOW_TRACK)
        drawTrack(cur_img, rightImg, ids, cur_pts, prevLeftPtsMap);

    /*------ step 4 : copy  -------*/
    // prevLeftPtsMap.clear();
    for(size_t i = 0; i < cur_pts.size(); i++)
    {
        // prevLeftPtsMap[ids[i]] = cur_pts[i];
        prevLeftPtsMap.insert(make_pair(ids[i],cur_pts[i]));
    }


    // prev_img.clear();
    // prev_img = cur_img;
    // prev_pts = cur_pts;
    std::swap(prev_pts, cur_pts);
    cv::swap(prev_img, cur_img);

}

void Tracker::drawTrack(const cv::Mat &imLeft, const cv::Mat &imRight, 
                               vector<int> &curLeftIds,
                               vector<cv::Point2f> &curLeftPts, 
                               map<int, cv::Point2f> &prevLeftPtsMap)
{
    cv::hconcat(imLeft, imRight, imTrack);

    for (size_t j = 0; j < curLeftPts.size(); j++)
    {
        double len = std::min(1.0, 1.0 * track_cnt[j] / 20);
        cv::circle(imTrack, curLeftPts[j], 2, cv::Scalar(255 * (1 - len), 0, 255 * len), 2);
    }

    map<int, cv::Point2f>::iterator mapIt;
    for (size_t i = 0; i < curLeftIds.size(); i++)
    {
        int id = curLeftIds[i];
        mapIt = prevLeftPtsMap.find(id);
        // cout << "id(" << id << ") count : " << prevLeftPtsMap.count(id) << '\n';
        if(mapIt != prevLeftPtsMap.end())
        {
            cv::arrowedLine(imTrack, curLeftPts[i], mapIt->second, cv::Scalar(0, 255, 0), 1, 8, 0, 0.2);
        }
    }

}

cv::Mat Tracker::getTrackImage()
{
    return imTrack;
}