#include<iostream>//c++ files
#include<opencv2\opencv.hpp>//opencv library function
#include<opencv2\imgproc\imgproc.hpp>//image processing
using namespace cv;
using namespace std;
/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/
//#define filename             "AVM.mp4"
#define filename             "../pictures/avm.png"
//#define filename             "rose.jpg"
#define SaveFileName         "result.png"
#define video 0
#define image 1
/*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/
#if video
int main(int argc, char** argv) {
    Mat src, gray;
    // video reading
    VideoCapture cap(filename);
    if (!cap.isOpened()) {
        cout << "Video can't be read" << endl;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;

    // harris corner detection
    int thresh = 150;
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros(src.size(), CV_32FC1);
    Mat roi_gray;
    int blockSize = 5;
    int apertureSize = 5;
    double k = 0.06;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'src'
        cap.read(src);
        cvtColor(src, gray, CV_BGR2GRAY);
        Mat src2 = src.clone();
        //cvtColor(src2, src2, CV_RGB2HSV);
        src2 = src2(Rect(src.cols * 1 / 3, src.rows * 1 / 5, src.cols * 1 / 3, src.rows * 3 / 5));
        Mat src3 = src2.clone();

        Mat image_r(src2.rows, src2.cols, CV_8UC1);
        Mat image_g(src2.rows, src2.cols, CV_8UC1);
        Mat image_b(src2.rows, src2.cols, CV_8UC1);
        Mat out[] = { image_r, image_g, image_b };
        int from_to[] = { 0,0, 1,1, 2,2 }; mixChannels(&src2, 1, out, 3, from_to, 3);
        Mat imageROI = src(Rect(src.cols * 1 / 3, src.rows * 1 / 5, src.cols * 1 / 3, src.rows * 3 / 5));
        //cvtColor(imageROI, roi_gray, CV_BGR2GRAY);

        //cvtColor(imageROI, imageROI, CV_BGR2HSV);
        cvtColor(imageROI, roi_gray, CV_BGR2GRAY);
        //morphologyEx(roi_gray, roi_gray, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));
        //morphologyEx(roi_gray, roi_gray, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));
        //morphologyEx(roi_gray, roi_gray, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));
        //morphologyEx(roi_gray, roi_gray, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));
        //morphologyEx(roi_gray, roi_gray, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(5, 5)));
        //threshold(image_g, image_g, 120, 255, THRESH_BINARY);
        /// Detecting corners
        cornerHarris(roi_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
        /// Normalizing
        normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
        convertScaleAbs(dst_norm, dst_norm_scaled);
        /// Drawing a circle around corners
        for (int j = 0; j < dst_norm.rows; j++)
        {
            for (int i = 0; i < dst_norm.cols; i++)
            {
                if ((int)dst_norm.at<float>(j, i) > thresh)
                {
                    circle(src2, Point(i, j), 5, Scalar(0, 0, 255), 1, 8, 0);
                    //circle(imageROI, Point(i, j), 5, Scalar(0, 0, 255), 1, 8, 0);
                }
            }
        }
        /// Showing the result
        //imshow("corners_windo", gray);
        // check if we succeeded
        if (src.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        //imshow("src", src);
        //imshow("gray", gray);
        /* ----------------- hough line transform ------------------- */
        Mat dst, cdst;
        Canny(src3, dst, 200, 250, 3);
        cvtColor(dst, cdst, CV_GRAY2BGR);
        vector<Vec4i> lines;
        HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
        for (size_t i = 0; i < lines.size(); i++)
        {
            Vec4i l = lines[i];
            line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
        }
        /* ---------------------------------------------------------- */
        //imshow("roi", imageROI);
        //imshow("roi_gray", roi_gray);
        imshow("dst", src2);
        imshow("cdst", cdst);
        if (waitKey(5) >= 0)
                break;
    }
    return 0;
}
# elif image
/// Trackbar strings
char* window_name = "DST";
int main() {
    // Initialize Matrix
    Mat src, BGR, HSV, gray, dst, LAB, test;
    src = imread(filename, 1);
    BGR = src.clone();
    cvtColor(src, HSV, CV_BGR2HSV);
    cvtColor(src, gray, CV_BGR2GRAY);
    cvtColor(src, LAB, CV_BGR2Lab);
    /// Create a window to display results

    namedWindow(window_name, 0);
    resizeWindow(window_name, 1000, 700);
    // BGR, HSV
    Mat B(BGR.rows, BGR.cols, CV_8UC1);
    Mat G(BGR.rows, BGR.cols, CV_8UC1);
    Mat R(BGR.rows, BGR.cols, CV_8UC1);
    Mat outBGR[] = { B, G, R };
    int from_toBGR[] = { 0,0, 1,1, 2,2 }; mixChannels(&BGR, 1, outBGR, 3, from_toBGR, 3);
    Mat H(HSV.rows, HSV.cols, CV_8UC1);
    Mat S(HSV.rows, HSV.cols, CV_8UC1);
    Mat V(HSV.rows, HSV.cols, CV_8UC1);
    Mat outHSV[] = { H, S, V };
    int from_toHSV[] = { 0,0, 1,1, 2,2 }; mixChannels(&HSV, 1, outHSV, 3, from_toHSV, 3);
    Mat L(LAB.rows, LAB.cols, CV_8UC1);
    Mat a(LAB.rows, LAB.cols, CV_8UC1);
    Mat b(LAB.rows, LAB.cols, CV_8UC1);
    Mat outLAB[] = { L, a, b };
    int from_toLAB[] = { 0,0, 1,1, 2,2 }; mixChannels(&LAB, 1, outLAB, 3, from_toLAB, 3);
    // Harris corner variables
    int thresh = 150;
    int blockSize = 6; //5
    int apertureSize = 5; //5
    double k = 0.06;
    for (;;)
    {
        // save, quit operate
        int input_key = waitKey(30);
        imshow(window_name, src);
        adaptiveThreshold(gray, test, 250, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5);

        /* -------------- Detecting corners -------------------- */
        //Mat dst_norm, dst_norm_scaled;
        //cornerHarris(test, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
        ///// Normalizing
        //normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
        //convertScaleAbs(dst_norm, dst_norm_scaled);
        ///// Drawing a circle around corners
        //for (int j = 0; j < dst_norm.rows; j++)
        //{
        //  for (int i = 0; i < dst_norm.cols; i++)
        //  {
        //      if ((int)dst_norm.at<float>(j, i) > thresh)
        //      {
        //          circle(src, Point(i, j), 5, Scalar(0, 0, 255), 1, 8, 0);
        //      }
        //  }
        //}
        /* ---------------------------------------------------------- */
        // ROI Image operation
        Mat roi_gray = Mat::zeros(src.rows, src.cols, CV_8UC1);
        /* ----------------- Condition -------------------------------- */
        for (int j = 0; j < src.rows; j++)
        {
            for (int i = 0; i < src.cols; i++)
            {
                // BGR, HSV condition
                if ((int)S.at<uchar>(j, i) <= 80 && (int)V.at<uchar>(j, i) >= 100 && (int)H.at<uchar>(j, i) <= 200
                    && (int)B.at<uchar>(j, i) >= 200)
                {
                    //circle(src, Point(i, j), 5, Scalar(255, 0, 0), 1, 8, 0);
                    roi_gray.at<uchar>(j, i) = 255;
                }
            }
        }
        /* -------------------------------------------------------------- */
        /* ------------------------- ROI -------------------------------- */
        Mat roi = src(Rect(src.cols * 1 / 3, src.rows * 1 / 5, src.cols * 1 / 3, src.rows * 3 / 5));
        roi_gray = roi_gray(Rect(src.cols * 1 / 3, src.rows * 1 / 5, src.cols * 1 / 3, src.rows * 3 / 5));
        /* -------------------------------------------------------------- */

        /* ----------------- hough line transform ------------------- */
        Mat dst, cdst;
        Canny(roi_gray, dst, 200, 250, 3);
        cvtColor(dst, cdst, CV_GRAY2BGR);

        morphologyEx(cdst, cdst, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(15, 15)));
        morphologyEx(cdst, cdst, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(15, 15)));
        morphologyEx(cdst, cdst, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(15, 15)));
        vector<Vec4i> lines;
        HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
        for (size_t i = 0; i < lines.size(); i++)
        {
            Vec4i l = lines[i];
            line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
        }
        /* ---------------------------------------------------------- */
        /* -------------- Detecting corners -------------------- */
        Mat dst_norm2, dst_norm_scaled2, dst2;
        //int thresh = 150;
        //int blockSize = 5;
        //int apertureSize = 5;
        //double k = 0.06;
        cornerHarris(roi_gray, dst2, blockSize, apertureSize, k, BORDER_DEFAULT);
        /// Normalizing
        normalize(dst2, dst_norm2, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
        convertScaleAbs(dst_norm2, dst_norm_scaled2);
        /// Drawing a circle around corners
        for (int j = 0; j < dst_norm2.rows; j++)
        {
            for (int i = 0; i < dst_norm2.cols; i++)
            {
                if ((int)dst_norm2.at<float>(j, i) > thresh)
                {
                    circle(roi, Point(i, j), 5, Scalar(255, 0, 0), 1, 8, 0);
                }
            }
        }
        /* ---------------------------------------------------------- */
        /* ----------------------Contour region making --------------- */
        Mat img_temp = roi_gray.clone();
        Mat img_contour, check, img2;
        vector<vector<Point>> contours;
        img2 = 255 - img_temp;
        img_contour = img2.clone();
        Mat hierarchy;
        findContours(img_contour, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        vector<vector<Point>> contours_poly(contours.size());
        vector<Rect> bound(contours.size());
        int contour_num = 0;
        check = img_temp.clone();
        vector<Rect> bound2(contours.size());
        for (int i = 0; i < contours.size(); i++)
        {
            approxPolyDP(Mat(contours[i]), contours_poly[i], 1, true); // approximate of contour
            bound[i] = boundingRect(Mat(contours_poly[i]));      // Make rectangular boundary
        }
        // Contour limitation for detecting license
        Mat drawing = roi.clone();
        Mat drawing2 = roi.clone();
        int refinery_count = 0;
        for (int i = 0; i < contours.size(); i++)
        {
            double ratio = abs((double)bound[i].height / bound[i].width);
            Point contour_WH = (bound[i].tl() - bound[i].br());
            drawContours(drawing, contours, i, Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
        }
        /* ---------------------------------------------------------- */
        // morphology operation
        morphologyEx(check, check, CV_MOP_DILATE, getStructuringElement(MORPH_RECT, Size(10, 10)));
        morphologyEx(check, check, CV_MOP_DILATE, getStructuringElement(MORPH_RECT, Size(10, 10)));
        morphologyEx(check, check, CV_MOP_DILATE, getStructuringElement(MORPH_RECT, Size(10, 10)));
        morphologyEx(check, check, CV_MOP_ERODE, getStructuringElement(MORPH_RECT, Size(10, 10)));
        //morphologyEx(check, check, CV_MOP_ERODE, getStructuringElement(MORPH_RECT, Size(10, 10)));
        //morphologyEx(check, check, CV_MOP_ERODE, getStructuringElement(MORPH_RECT, Size(10, 10)));

        /* -------------- Detecting corners -------------------- */
        Mat dst_norm3, dst_norm_scaled3, dst3;
        //int thresh = 150;
        //int blockSize = 5;
        //int apertureSize = 5;
        //double k = 0.06;
        cornerHarris(check, dst3, blockSize, apertureSize, k, BORDER_DEFAULT);
        /// Normalizing
        normalize(dst3, dst_norm3, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
        convertScaleAbs(dst_norm3, dst_norm_scaled3);
        /// Drawing a circle around corners
        for (int j = 0; j < dst_norm3.rows; j++)
        {
            for (int i = 0; i < dst_norm3.cols; i++)
            {
                if ((int)dst_norm3.at<float>(j, i) > thresh)
                {
                    circle(drawing, Point(i, j), 5, Scalar(0, 255, 0), 1, 8, 0);
                }
            }
        }
        /* ---------------------------------------------------------- */
        if (input_key == 'q' || input_key == 'Q') {
            cout << "Program Termination" << endl;
            break;
        }
        else if (input_key == 'c' || input_key == 'C') imwrite(SaveFileName, dst);
        //else if (input_key == 's' || input_key == 'S') cout << "T_val =  " << T_val << endl;
        input_key = 0;
    }

    return 0;
}
# endif
