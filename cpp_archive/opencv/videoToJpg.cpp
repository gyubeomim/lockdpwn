/*
	c++ ==> opencv, 동영상파일을 파라미터로 넣어주면 한 프레임씩 사진을 jpg 파일로 출력하는 코드
*/
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>

using namespace std;

int main(int argc, char **argv){
	IplImage *img;
	CvCapture *capture;

	capture = cvCaptureFromFile(argv[1]);

	int fps;
	int count = 0;

	if (capture){
		while (1){
			img = cvQueryFrame(capture);
			if (!img) break;

			cvNamedWindow("image");
			cvShowImage("image", img);

			string filename;
			filename = cv::format("capture%03d.jpg", count);
			cvSaveImage(filename.c_str(), img);
			cvWaitKey(1);
			count++;
		}
	}

	cvReleaseCapture(&capture);

	return 0;
}