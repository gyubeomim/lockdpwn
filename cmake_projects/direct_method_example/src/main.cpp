#include "../include/optimizer.h"
#include "../include/direct.h"
#include "../include/dataset.h"

// comment(edward): do LBA with keyframes and current frame
void lba_test(){
  //char c = 0;
  std::map<size_t, std::string> im0_filenames, im1_filenames;
  real offset;
  Intrinsic* intrinsic;
  load_kitti<real>(im0_filenames, im1_filenames, intrinsic, offset);
  Sophus::SE3<real> g_rl;
  g_rl.translation() = Eigen::Matrix<real,3,1>(-offset,0., 0.);
  DirectMethod method(intrinsic);
  method.set_stereo(&g_rl);

  size_t start_im = 200;
  for(size_t n = start_im; n < im1_filenames.size(); n++){
    std::string fn0 = im0_filenames.at(n);
    cv::Mat im0 = cv::imread(fn0, cv::IMREAD_GRAYSCALE);
    std::string fn1 = im1_filenames.at(n);
    cv::Mat im1 = cv::imread(fn1, cv::IMREAD_GRAYSCALE);
    method.put_image(im0, im1);
  }
  printf("end of images\n");
  return;
}

void zoomout_test(){
  std::map<size_t, std::string> im0_filenames, im1_filenames;
  real offset;
  Intrinsic* intrinsic;
  load_kitti<real>(im0_filenames, im1_filenames, intrinsic, offset);
  std::string fn0 = im1_filenames.at(0);
  cv::Mat im0 = cv::imread(fn0, cv::IMREAD_GRAYSCALE);
  zoomout_test(im0);
  return;
}

void invd_test(){
  std::map<size_t, std::string> im0_filenames, im1_filenames;
  Intrinsic* intrinsic;
  real offset;
  load_kitti<real>(im0_filenames, im1_filenames, intrinsic, offset);
  std::string fn0 = im0_filenames.at(0);
  std::string fn1 = im1_filenames.at(0);
  cv::Mat im0 = cv::imread(fn0, cv::IMREAD_GRAYSCALE);
  cv::Mat im1 = cv::imread(fn1, cv::IMREAD_GRAYSCALE);
  motion_invd_test(im0, im1, intrinsic, offset, INVD_TEST);
}

void motion_test(){
  std::map<size_t, std::string> im0_filenames, im1_filenames;
  Intrinsic* intrinsic;
  real offset;
  load_kitti<real>(im0_filenames, im1_filenames, intrinsic, offset);
  std::string fn0 = im0_filenames.at(0);
  std::string fn1 = im1_filenames.at(0);
  cv::Mat im0 = cv::imread(fn0, cv::IMREAD_GRAYSCALE);
  cv::Mat im1 = cv::imread(fn1, cv::IMREAD_GRAYSCALE);
  motion_invd_test(im0, im1, intrinsic, offset, MOTION_TEST);
}

void loop_detect_test(){
  printf("TODO Loop detection doesn't working yet.\n");
  exit(1);
  std::map<size_t, std::string> im0_filenames, im1_filenames;
  Eigen::Matrix<real,3,3> K;
  real offset;
}

void gamma_test(){
  char c = 0;
  double gamma = 1.;
  double mult = 1.02;
  printf("press [a], [s] to change gamma, [r] to reset 1.\n");
  cv::Mat im0 = cv::imread("/home/geo/mydataset/cmos_fisheyes/seq0/0/2396.png");
  cv::Mat im1 = cv::imread("/home/geo/mydataset/cmos_fisheyes/seq0/0/2400.png");
  cv::Mat lut(1,256,CV_8UC1);
  uchar* ptr = lut.ptr();
  while(c != 'q'){
    for(int i=0; i < 256; i++)
      ptr[i] = cv::saturate_cast<uchar>( std::pow(i/255., gamma) * 255.);
    cv::Mat dst;
    cv::LUT(im1, lut, dst);
    cv::putText(dst, "gamma="+std::to_string(gamma), cv::Point(50,50), 0, .5, cv::Scalar(0,0,255),2);
    cv::imshow("im0 without correction", im0);
    cv::imshow("im1 with correction", dst);
    c = cv::waitKey(0);
    if(c=='a') gamma /= mult;
    else if(c=='s') gamma *= mult;
    else if(c=='r') gamma = 1.;
  }
}

void ris_rectify_test(){
  std::map<size_t, std::string> im0_filenames, im1_filenames;
  Intrinsic *intrinsic0, *intrinsic1;
  Sophus::SE3<real> g_rl;
  FeatureCriteria* feature_criteria = NULL;
  load_ris<real>(im0_filenames, im1_filenames, intrinsic0, intrinsic1, g_rl, feature_criteria);
  Rectifier* rectifier0 = intrinsic0->create_rectifier();
  Rectifier* rectifier1 = intrinsic1->create_rectifier();

  bool stopmode = false;
  auto it_start = im0_filenames.begin(); // + n??
  for(auto it = it_start; it != im0_filenames.end(); it++){
    cv::Mat im0 = cv::imread(it->second, cv::IMREAD_GRAYSCALE);
    cv::Mat im1 = cv::imread(im1_filenames.at(it->first), cv::IMREAD_GRAYSCALE);
    cv::Mat dst0 = rectifier0->rectify(im0);
    cv::Mat dst1 = rectifier1->rectify(im1);
    cv::imshow("rect0", dst0);
    cv::imshow("rect1", dst1);
    if(it == it_start){
      cv::moveWindow("rect0", 100,100);
      cv::moveWindow("rect1", 100,100);
    }
    char c = cv::waitKey(stopmode?0:1);
    if(c=='q') break;
    else if(c=='s') stopmode = !stopmode;
  }

  return;
}

void shuttum_rectify_test(){
  std::map<size_t, std::string> im0_filenames;
  std::map<size_t, std::string> im1_filenames;
  Sophus::SE3<real> g_rl;
  Intrinsic *intrinsic0, *intrinsic1;
  FeatureCriteria* feature_criteria;
  load_shuttum(im0_filenames,im1_filenames, intrinsic0, intrinsic1, g_rl, feature_criteria);
  Rectifier* rectifier0 = intrinsic0->create_rectifier();
  bool stopmode = false;
  auto it_start = im0_filenames.begin(); // + n??
  for(auto it = it_start; it != im0_filenames.end(); it++){
    cv::Mat im0 = cv::imread(it->second); // cv::IMREAD_GRAYSCALE);
    cv::Mat dst = rectifier0->rectify(im0);
    cv::imshow("src", im0);
    cv::imshow("rect", dst);
    char c = cv::waitKey(stopmode?0:1);
    if(c=='q') break;
    else if(c=='s') stopmode = !stopmode;

  }
  return;
}

void ris_test(){
  std::map<size_t, std::string> im0_filenames, im1_filenames;
  Intrinsic *intrinsic0, *intrinsic1;
  Sophus::SE3<real> g_rl;
  FeatureCriteria* feature_criteria = NULL;
  load_ris<real>(im0_filenames, im1_filenames, intrinsic0, intrinsic1, g_rl, feature_criteria);
  FisheyeDirectMethod method(intrinsic0, intrinsic1, g_rl, feature_criteria, 1);
  bool stopmode = false;
  auto it_start = im0_filenames.begin(); // + n??
  for(int i =0; i < 1200; i++) it_start++;
  for(auto it = it_start; it != im1_filenames.end(); it++){
    cv::Mat im0 = cv::imread(it->second, cv::IMREAD_GRAYSCALE);
    cv::Mat im1 = cv::imread(im1_filenames.at(it->first), cv::IMREAD_GRAYSCALE);
    method.put_image(im0, im1);
  }
  return;
}


void refac_test(){
  printf("refac test\n");
  std::map<size_t, std::string> im0_filenames, im1_filenames;
  Intrinsic *intrinsic0, *intrinsic1;
  Sophus::SE3<real> g_rl;
  FeatureCriteria* feature_criteria = NULL;
  load_ris<real>(im0_filenames, im1_filenames, intrinsic0, intrinsic1, g_rl, feature_criteria);

  int levels = 5;
  auto it_start = im0_filenames.begin(); // + n??
  for(auto it = it_start; it != im1_filenames.end(); it++){
    cv::Mat im0 = cv::imread(it->second, cv::IMREAD_GRAYSCALE);
    std::shared_ptr<Images> sp = std::make_shared<Images>(im0, levels);


    break;
  }
  return;
}

void shuttum_test(){
  std::map<size_t, std::string> im0_filenames;
  std::map<size_t, std::string> im1_filenames;
  Sophus::SE3<real> g_rl;
  Intrinsic *intrinsic0, *intrinsic1;
  FeatureCriteria* feature_criteria;
  load_shuttum(im0_filenames,im1_filenames, intrinsic0, intrinsic1, g_rl, feature_criteria);
  FisheyeDirectMethod method(intrinsic0, intrinsic1, g_rl, feature_criteria, 0);
  auto it = im0_filenames.begin(); // + n??
  {
    cv::Mat im0 = cv::imread(it->second, cv::IMREAD_GRAYSCALE);
    cv::Mat im1 = cv::imread(im1_filenames.at(it->first), cv::IMREAD_GRAYSCALE);
    std::cout << "im0 = " << it->second << std::endl;
    std::cout << "im1 = " << im1_filenames.at(it->first) << std::endl;
    method.put_image(im0, im1);
  }
  for(int i =0; i < 13; i++) it++;
  {
    cv::Mat im0 = cv::imread(it->second, cv::IMREAD_GRAYSCALE);
    cv::Mat im1 = cv::imread(im1_filenames.at(it->first), cv::IMREAD_GRAYSCALE);
    method.put_image(im0, im1);
  }
  cv::waitKey(0);
  return;
}

int main(int argc, char* argv[]){
  if(argc > 1){
    char* str = argv[argc-1];
    if(std::string("invd").compare(str)==0)
      invd_test();
    else if(std::string("opt").compare(str)==0)
      optimizer_test();
    else if(std::string("zoom").compare(str)==0)
      zoomout_test();
    else if(std::string("motion").compare(str)==0)
      motion_test();
    else if(std::string("loop").compare(str)==0)          // not working
      loop_detect_test();
    else if(std::string("shuttum").compare(str)==0)       // not working
      shuttum_test();
    else if(std::string("ris").compare(str)==0)           // not working
      ris_test();
    else if(std::string("shuttum_rect").compare(str)==0)  // not working
      shuttum_rectify_test();
    else if(std::string("ris_rect").compare(str)==0)      // not working
      ris_rectify_test();
    else if(std::string("gamma").compare(str)==0)         // crash
      gamma_test();
    else if(std::string("distortion").compare(str)==0)
      distortion_test();
    else if(std::string("graph").compare(str)==0)
      graph_test();
    else if(std::string("refac").compare(str)==0)         // not working
      refac_test();
    else if(std::string("lba").compare(str)==0)
      lba_test();
  }
  return 0;
}
