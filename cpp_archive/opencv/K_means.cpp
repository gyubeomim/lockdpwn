#include "stdafx.h"
#include <opencv2/opencv.hpp>

static const int MAX_CLUSTERS = 3;	// 클러스터 수

static struct sSampleParam {
	int no_sample;				// 셈플 데이터의 수
	double mean_x, mean_y;		// x, y의 평균
	double stdev_x, stdev_y;	// x, y의 표준 편차
	CvScalar color_bg;			// 배경 색
} sample_param[MAX_CLUSTERS] = {
	{ 500,  500, 200,  60,  30, CV_RGB(255, 0, 0), },
	{ 1500, 200, 500, 100,  80, CV_RGB(0, 255, 0), },
	{ 1000, 400, 700,  60, 100, CV_RGB(0, 0, 255), },
};


void K_Means ()
{
	cv::RNG rng;

	IplImage *img = cvCreateImage (cvSize (1000, 1000), IPL_DEPTH_8U, 3);
	cvZero (img);

	cvNamedWindow ("result", CV_WINDOW_AUTOSIZE);

	// 학습 데이터의 총 수를 카운트 한다.
	int sample_count = 0;
	for (int i=0; i<MAX_CLUSTERS; i++) sample_count += sample_param[i].no_sample;

	CvMat *points   = cvCreateMat (sample_count, 2, CV_32FC1);
	CvMat *clusters = cvCreateMat (sample_count, 1, CV_32SC1);
	
	// 각 클러스터 별로 정규분포를 가지는 데이터를 무작위로 생성
	for (int i=0, k=0; i<MAX_CLUSTERS; i++){
		for (int j=0; j<sample_param[i].no_sample; j++){
			CV_MAT_ELEM(*points,  float,k,0) = (float)(sample_param[i].mean_x + rng.gaussian(sample_param[i].stdev_x));
			CV_MAT_ELEM(*points,  float,k,1) = (float)(sample_param[i].mean_y + rng.gaussian(sample_param[i].stdev_y));
			// CV_MAT_ELEM(*clusters,long, k,0) = i;
			k++;
		}
	}

	// MAX_K-means에 의한 클러스터링
	cvKMeans2 (points, MAX_CLUSTERS, clusters, cvTermCriteria (CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0));

	// 클러스터마다 색을 바꾸어 샘플을 그림
	for (int k=0; k<sample_count; k++){
		int x = cvRound(CV_MAT_ELEM(*points, float,k,0));
		int y = cvRound(CV_MAT_ELEM(*points, float,k,1));
		int c = cvRound(CV_MAT_ELEM(*clusters,long, k,0));

		cvCircle (img, cvPoint(x, y), 2, sample_param[c].color_bg, CV_FILLED);
	}

	// 이미지를 표시
	cvShowImage ("result", img);

	// 키를 누르면 종료
	cvWaitKey (0);

	cvReleaseMat (&points);
	cvReleaseMat (&clusters);

	cvDestroyWindow ("result");
	cvReleaseImage (&img);
}


int main()
{
	K_Means ();

	return 0;
}