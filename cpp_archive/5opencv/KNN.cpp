#include <opencv2/opencv.hpp>
#include <opencv/ml.h>
#include <opencv/highgui.h>
#include <time.h>

static const int MAX_K = 10;
static const int MAX_CLASS = 3;	// 클래스 수

static struct sSampleParam {
	int no_sample;				// 셈플 데이터의 수
	double mean_x, mean_y;		// x, y의 평균
	double stdev_x, stdev_y;	// x, y의 표준 편차
	CvScalar color_pt;			// 셈플 색
	CvScalar color_bg;			// 배경 색
} sample_param[MAX_CLASS] = {
	{ 500,  500, 200,  60,  30, CV_RGB(180, 0, 0), CV_RGB(255, 0, 0), },
	{ 1500, 200, 500, 100,  80, CV_RGB(0, 180, 0), CV_RGB(0, 255, 0), },
	{ 1000, 400, 700,  60, 100, CV_RGB(0, 0, 180), CV_RGB(0, 0, 255), },
};

void KNN ()
{
	cv::RNG rng;

	IplImage *img = cvCreateImage (cvSize (1000, 1000), IPL_DEPTH_8U, 3);
	cvZero (img);

	cvNamedWindow ("result", CV_WINDOW_AUTOSIZE);

	// 학습 데이터의 총 수를 카운트 한다.
	int sample_count = 0;
	for (int i=0; i<MAX_CLASS; i++) sample_count += sample_param[i].no_sample;

	// 학습 데이터와 클래스를 할당할 행렬 생성
	CvMat *train_data  = cvCreateMat (sample_count, 2, CV_32FC1);
	CvMat *train_class = cvCreateMat (sample_count, 1, CV_32SC1);
	
	// 각 클래스 별로 정규분포를 가지는 학습 데이터를 무작위로 생성
	for (int i=0, k=0; i<MAX_CLASS; i++){
		for (int j=0; j<sample_param[i].no_sample; j++){
			CV_MAT_ELEM(*train_data, float,k,0) = (float)(sample_param[i].mean_x + rng.gaussian(sample_param[i].stdev_x));
			CV_MAT_ELEM(*train_data, float,k,1) = (float)(sample_param[i].mean_y + rng.gaussian(sample_param[i].stdev_y));
			CV_MAT_ELEM(*train_class,long, k,0) = i;
			k++;
		}
	}
	
	// learn classifier
	CvKNearest knn (train_data, train_class, 0, false, MAX_K);

	CvMat *nearests = cvCreateMat (1, MAX_K, CV_32FC1);

	// KNN 분류기가 이미지의 모든 픽셀에 대해 각 픽셀이 
	// 어느 클래스에 속하는지 추정하여 클래스를 할당한다.
	for (int x=0; x<img->width; x++) {
		for (int y=0; y<img->height; y++) {
			float sample_[2] = {(float)x, (float)y};
			CvMat sample = cvMat (1, 2, CV_32FC1, sample_);

			// KNN 분류기가 주어진 픽셀이 어느 클래스에 속하는지 추정한다.
			float response = knn.find_nearest (&sample, MAX_K, 0, 0, nearests, 0);

			// 이미지에 추정된 클래스를 색으로 표시한다.
			cvSet2D (img, y, x, sample_param[cvRound(response)].color_pt); 
		}
	}

	// 학습 데이터를 이미지에 그린다.
	for (int k=0; k<sample_count; k++) {
		int x = cvRound(CV_MAT_ELEM(*train_data, float,k,0));
		int y = cvRound(CV_MAT_ELEM(*train_data, float,k,1));
		int c = cvRound(CV_MAT_ELEM(*train_class,long, k,0));

		cvCircle (img, cvPoint(x, y), 2, sample_param[c].color_bg, CV_FILLED);
	}

	cvShowImage ("result", img);
	
	// 키를 누르면 종료
	cvWaitKey (0);

	cvReleaseMat (&train_class);
	cvReleaseMat (&train_data);
	cvReleaseMat (&nearests);

	cvDestroyWindow ("result");
	cvReleaseImage (&img);
}

int main()
{
	KNN ();

	return 0;
}