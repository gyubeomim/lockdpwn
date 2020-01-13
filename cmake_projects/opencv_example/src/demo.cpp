#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
int main(int, char *argv[]){
    Mat in_image, out_image;
    in_image = imread(argv[1], IMREAD_UNCHANGED);
    return 0;
}
