/*
	c++ ==> opencv, 웹캠에서 얼굴인식 사각형을 출력하는 코드
*/
#include <iostream> 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp> 

int main(int argc, char *argv[]) {
	// ------------------------------------------------------------------------- 
	// webcam routine 
	cv::VideoCapture capture(0);

	if (!capture.isOpened()) {
		std::cerr << "Could not open camera" << std::endl; return 0;
	}

	// create a window 
	cv::namedWindow("webcam", 1);
	// ------------------------------------------------------------------------- 
	// face detection configuration 
	cv::CascadeClassifier face_classifier;
	face_classifier.load("C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml");

	while (true) {
		bool frame_valid = true;
		cv::Mat frame_original;
		cv::Mat frame;

		try {
			capture >> frame_original;
			// get a new frame from webcam 
			cv::resize(frame_original, frame, cv::Size(frame_original.cols / 2, frame_original.rows / 2), 0, 0, CV_INTER_NN);
			// downsample 1/2x 
		}
		catch (cv::Exception& e) {
			std::cerr << "Exception occurred. Ignoring frame... " << e.err << std::endl;
			frame_valid = false;
		}

		if (frame_valid) {
			try {
				// convert captured frame to gray scale & equalize 
				cv::Mat grayframe;
				cv::cvtColor(frame, grayframe, CV_BGR2GRAY);
				cv::equalizeHist(grayframe, grayframe);
				// ------------------------------------------------------------- 
				// face detection routine 
				// a vector array to store the face found 
				std::vector<cv::Rect> faces;

				face_classifier.detectMultiScale(grayframe, faces, 1.1, 3,
					// increase search scale by 10% each pass 3, 
					// merge groups of three detections 
					CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
					cv::Size(30, 30));

				// ------------------------------------------------------------- 
				// draw the results 
				for (int i = 0; i < faces.size(); i++) {
					cv::Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
					cv::Point tr(faces[i].x, faces[i].y);
					cv::rectangle(frame, lb, tr, cv::Scalar(0, 255, 0), 3, 4, 0);
				}

				// print the output 
				cv::imshow("webcam", frame);
			}
			catch (cv::Exception& e) {
				std::cerr << "Exception occurred. Ignoring frame... " << e.err << std::endl;
			}
		}
		if(cv::waitKey(1) == 27) break;
	}
	// VideoCapture automatically deallocate camera object 
	return 0;
}

