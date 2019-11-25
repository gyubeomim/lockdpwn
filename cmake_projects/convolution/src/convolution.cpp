#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Core>

void Convolution(int input_width, uchar* input_img,
                 int kernel_width, int kernel_height, Eigen::MatrixXd kernel,
                 int output_width, int output_hegiht, uchar* output_img)
{
  int num_channels = 1;

  for (int i = 0; i < output_width; ++i) {
    int k = i + (kernel_width - 1);
    for (int j = 0; j < output_hegiht; ++j) {
      int l = j + (kernel_height - 1);
      for (int m = 0; m < kernel_width; ++m) {
        for (int n = 0; n < kernel_height; ++n) {
          for (int channel = 0; channel < num_channels; ++channel)
            output_img[num_channels * (i + output_width * j) + channel] += uchar(input_img[num_channels * ((k - m) + input_width * (l - n)) + channel] * kernel(m, n));
        }
      }
    }
  }
}

int main(int argc, char* argv[]) {
  cv::Mat input_img = cv::imread("/home/edward/Downloads/000000.png", CV_8UC1);
  if (input_img.empty())
    return 1;

  int input_width = input_img.size().width, intput_height = input_img.size().height;

  int kernel_width = 3, kernel_height = 3;

  Eigen::MatrixXd kernel;
  kernel.resize(kernel_width, kernel_height);

  for (int i = 0; i < kernel_width; ++i)
    for (int j = 0; j < kernel_height; ++j)
      kernel(i, j) = .5;

  int output_width = input_width - (kernel_width - 1), output_height = intput_height - (kernel_height - 1);

  cv::Mat output_img = cv::Mat::zeros(cv::Size(output_width, output_height), CV_8UC1);

  Convolution(input_width, input_img.data,
              kernel_width, kernel_height, kernel,
              output_width, output_height, output_img.data);

  cv::imshow("", output_img);
  cv::waitKey(0);

  return 0;
}
