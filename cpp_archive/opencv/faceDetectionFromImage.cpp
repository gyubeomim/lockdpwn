/*
	c++ ==> opencv, 특정 사진에서 얼굴 + 눈을 인식하는 사각형을 출력하는 코드
					vs에서 relaes x64로 하니 정상적으로 작동한다
*/
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

String face_cascade = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml";
String eye_cascade = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
String img_name = "face2.jpg";

CascadeClassifier face;
CascadeClassifier eye;

int main(int argc, const char *argv[]) {
	Mat img = imread(img_name);

	if (img.data == NULL) {
		cout << img_name << "fail image open" << endl;
		return -1;
	}

	if (!face.load(face_cascade) || !eye.load(eye_cascade)) {
		cout << "Cascade fail file open " << endl;
		return -1;
	}

#pragma region face recog
	Mat gray;
	cvtColor(img, gray, CV_RGB2GRAY);

	vector<Rect> face_pos;  
	face.detectMultiScale(gray, face_pos, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(10, 10));

	for (int i = 0; i < (int)face_pos.size(); i++) {
		rectangle(img, face_pos[i], Scalar(0, 255, 0), 2);
	}
#pragma endregion


#pragma region eye recog
	for (int i = 0; i < (int)face_pos.size(); i++) {
		vector<Rect> eye_pos; 
		Mat roi = gray(face_pos[i]);

		eye.detectMultiScale(roi, eye_pos, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(10, 10));

		for (int j = 0; j < (int)eye_pos.size(); j++) {
			Point center(face_pos[i].x + eye_pos[j].y + (eye_pos[j].width / 2),
				face_pos[i].y + eye_pos[j].y + (eye_pos[j].height / 2));

			int radius = cvRound((eye_pos[j].width + eye_pos[j].height) * 0.2);
			circle(img, center, radius, Scalar(0, 0, 255), 2);
		}
	}
#pragma endregion

	namedWindow("face recognition");	
	imshow("face recognition", img);
	waitKey(); 

	return 0;
}


