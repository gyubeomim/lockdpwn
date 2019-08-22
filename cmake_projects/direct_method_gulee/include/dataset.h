#ifndef DATASET_H_
#define DATASET_H_
#include "intrinsic.h"

const std::string resource_path = RESOURCE;

template <typename T>
void load_kitti(std::map<size_t, std::string>& im0_filenames,
                std::map<size_t, std::string>& im1_filenames,
                Intrinsic*& intrinsic,
                T& offset)
{
  // const std::string odom_path = resource_path+"/kitti/odometry_dataset";
  const std::string odom_path = "/home/atlas1/datasets/kitti/data_odometry";
  const std::string sequences = "00";
  const std::string im0_path = odom_path+"/sequences/"+sequences+"/image_0";
  const std::string im1_path = odom_path+"/sequences/"+sequences+"/image_1";
  const std::string calib_path  = odom_path + "/sequences/"+sequences+"/calib.txt";

  {
    std::ifstream fs;
    fs.open(calib_path);

    std::string str;
    std::getline(fs, str);

    float elem[12];
    sscanf(str.c_str(),"P0: %f %f %f %f %f %f %f %f %f %f %f %f \n", elem, elem+1, elem+2, elem+3, elem+4, elem+5, elem+6, elem+7, elem+8, elem+9, elem+10, elem+11);

    Eigen::Matrix<real,3,3> K;

    for(size_t i = 0; i < 3; i++)
      for(size_t j = 0; j < 3; j++)
        K(i,j) = elem[4*i+j];

    intrinsic = new RadTanIntrinsic(K, Eigen::Matrix<real,4,1>(0.,0.,0.,0.));

    std::getline(fs, str);
    sscanf(str.c_str(),"P1: %f %f %f %f %f %f %f %f %f %f %f %f \n", elem, elem+1, elem+2, elem+3, elem+4, elem+5, elem+6, elem+7, elem+8, elem+9, elem+10, elem+11);
    offset = std::abs(elem[3]) * 0.001; // mm -> meter
  }

  boost::filesystem::directory_iterator it{im0_path}, end;
  for(; it != end; it++)
  {
    std::string str = it->path().filename().stem().string();
    if(it->path().filename().extension() != ".png")
    {
      std::cout << it->path().filename() << std::endl;
      std::cout << it->path().filename().extension() << std::endl;
      std::cout << "not png" << std::endl;
      exit(1);
    }

    size_t i = std::stoi(str);
    im0_filenames[i] = it->path().string();
    im1_filenames[i] = im1_path+"/" + it->path().filename().string();
  }
}

template <typename T>
void load_shuttum(std::map<size_t, std::string>& im0_filenames,
                  std::map<size_t, std::string>& im1_filenames,
                  Intrinsic*& intrinsic0,
                  Intrinsic*& intrinsic1,
                  Sophus::SE3<T>& g_rl, // coord from l to r.  g for just function g(x)
                  FeatureCriteria* feature_criteria)
{
  class ShuttumFeatureCriteria : public FeatureCriteria{};

  feature_criteria = new ShuttumFeatureCriteria();

  const std::string seq = "01";
  const std::string dataset_path = resource_path + "/shuttum/";
  const std::string params = dataset_path + seq + "/params/opencv_params.yaml";

  std::vector<std::string> cams = {"cam1", "cam2"};

  for(int i = 0; i < 2; i++)
  {
    const std::string cam = cams.at(i);
    const std::string gamma = dataset_path + seq + "/params/"+cam+"/gamma.txt";
    const std::string vignette = dataset_path + seq + "/params/"+cam+"/vignette.png";
    const std::string im_path  = dataset_path + seq + "/frames/"+cam;

    boost::filesystem::directory_iterator it{dataset_path+seq+"/frames/"+cam}, end;

    for(; it != end; it++)
    {
      std::string str = it->path().filename().stem().string();

      if(it->path().filename().extension() != ".jpeg")
        continue;

      size_t n = std::stoi(str);

      if(i==0)
        im0_filenames[n] = it->path().string();
      else
        im1_filenames[n] = it->path().string();

    }
  }

  cv::FileStorage fs(params, cv::FileStorage::READ);
  cv::FileNode node = fs["params"];

  int n = 0;

  for(auto it = node.begin(); it!=node.end(); it++)
  {
    cv::FileNode each = *it;
    std::vector<double> vec;
    each["radtan"] >> vec;
    Eigen::Matrix<T, 4,1> distortion;

    distortion << vec.at(0), vec.at(1), vec.at(2), vec.at(3);// radtan
    //distortion << vec.at(1), 0., 0., 0.; // for fisheye

    each["intrinsics"] >> vec;
    Eigen::Matrix<T, 3,3> K;
    K << vec.at(0), 0., vec.at(2),
        0., vec.at(1), vec.at(3),
        0., 0., 1.;
    std::cout << "K = \n" << K << std::endl;
    std::cout << "distortion = " << distortion.transpose() << std::endl;

    if(n==0)
    {
      intrinsic0 = new RadTanIntrinsic(K, distortion);
    }
    else if(n==1)
    {
      intrinsic1 = new RadTanIntrinsic(K, distortion);
      each["transform"] >> vec;

      Eigen::Matrix<T,3,3> R;
      R << vec.at(0), vec.at(1), vec.at(2),
          vec.at(4), vec.at(5), vec.at(6),
          vec.at(8), vec.at(9), vec.at(10);

      Eigen::Matrix<T,3,1> t;
      t << vec.at(3), vec.at(7), vec.at(11);

      Sophus::SE3<real> g_lr;
      g_lr.translation() = t;
      g_lr.setRotationMatrix(R);
      g_rl = g_lr.inverse();

      std::cout << "g_lr = \n" << g_lr.matrix3x4() << std::endl;

      break;
    }
    n++;
  }

  std::cout << "grl = \n" << g_rl.matrix3x4() << std::endl;
  return;
}


template <typename T>
void load_ris(std::map<size_t, std::string>& im0_filenames,
              std::map<size_t, std::string>& im1_filenames,
              Intrinsic*& intrinsic0,
              Intrinsic*& intrinsic1,
              Sophus::SE3<T>& g_rl, // coord from l to r.  g for just function g(x)
              FeatureCriteria*& feature_criteria)
{
  class RisFeatureCriteria : public FeatureCriteria{
   public:
    RisFeatureCriteria(int width, int height)
        : width_(width), height_(height), radius_(250)
    {
    }
    virtual size_t max_points_for_frame() const {
      return 100;
    }
    virtual std::vector<cv::Point2f> corrner_detect(cv::Mat src) const{
      int max_coners = 100;
      double quality_level = 0.01;
      double min_distance = 40.;
      int block_size = 4;
      bool use_harris = true;
      std::vector<cv::Point2f> corners;
      cv::goodFeaturesToTrack(src,
                              corners,
                              max_coners,
                              quality_level,
                              min_distance,
                              cv::noArray(),
                              block_size, use_harris);
      return corners;
    }

    virtual bool is_enable_point(const Eigen::Matrix<real,2,1>& uv) const {
      Eigen::Matrix<real,2,1> cp(width_/2, height_/2);
      real r = (uv-cp).norm();
      if(r > radius_)
        return false;
      real offset = 50;
      if(uv[0] < offset) return false;
      if(uv[1] < offset) return false;
      if( width_ - uv[0] < offset ) return false;
      if(height_ - uv[1] < offset ) return false;
      return true;
    }

    virtual cv::Mat draw_mask(cv::Mat src) const {
      real offset = 30;
      Eigen::Matrix<real,2,1> cp(width_/2, height_/2);
      auto c1 = CV_RGB(0,255,255);
      cv::Mat m1 = cv::Mat(src.size(), CV_8UC3, c1);
      cv::circle(m1, cv::Point(cp[0],cp[1]), radius_, CV_RGB(255,255,255),-1);
      cv::bitwise_not(m1, m1);
      //auto c2 = CV_RGB(0,0,255);
      auto c2 = CV_RGB(255,0,0);
      cv::rectangle(m1, cv::Point(0,0), cv::Point(width_,offset), c2,-1);
      cv::rectangle(m1, cv::Point(0,0), cv::Point(offset,height_), c2,-1);
      cv::rectangle(m1, cv::Point(width_-offset, 0), cv::Point(width_,height_), c2,-1);
      cv::rectangle(m1, cv::Point(0, height_-offset), cv::Point(width_,height_),c2,-1);
      cv::Mat dst = src + 0.15*m1;
      return dst;
    }

    virtual bool is_keyframe(const Frame* frame) const{
      Eigen::MatrixXi grid(4,1);
      int min_n = 5;
      cv::Size size = frame->images()->src().size();
      float w = (float)size.width / (float)grid.rows();
      float h = (float)size.height / (float)grid.cols();
      grid.setZero();
      for(auto point_it = frame->points().begin();
          point_it != frame->points().end();
          point_it++){
        Point* point = *point_it;
        Eigen::Matrix<real,3,1> Xc = frame->g_cw() * point->node()->xw();
        Eigen::Matrix<real,2,1> x = frame->intrinsic()->proj(Xc);
        int ix = x[0] / w;
        int iy = x[1] / h;
        if(ix < 0 || iy < 0 || ix >= grid.rows() || iy >= grid.cols() )
          continue;
        grid(ix,iy) += 1;
      }
      bool condition = false;
      for(int ix = 0 ; ix < grid.rows(); ix++)
        for(int iy = 0; iy < grid.cols(); iy++)
          if(grid(ix,iy) < min_n ){
            condition = true;
            break;
          }
      return condition;
    }

   private:
    const int radius_;
    const int width_;
    const int height_;
  };

  const std::string sequences = "seq0";
  const std::string dataset_path = resource_path+"/cmos_fisheyes";
  const std::string im0_path = dataset_path+"/"+sequences+"/0";
  const std::string im1_path = dataset_path+"/"+sequences+"/1";

  Eigen::Matrix<T,3,3> K0, K1;
  Eigen::Matrix<T, 4,1> D0, D1;

  K0 << 247.07528,  0.00000,  321.96885,
      0.00000,  246.54287,  208.70554,
      0.00000,  0.00000,  1.0000;
  K1 << 245.31467,  0.00000,  340.99825,
      0.00000,  244.29709,  245.51228,
      0.00000,  0.00000,  1.0000;
  D0 << -0.07030,  0.01070,  -0.00295,  -0.00347;
  D1 << -0.07166,  0.02483,  -0.02186,  0.00533;

  intrinsic0 = new FisheyeIntrinsic(K0, D0);
  intrinsic1 = new FisheyeIntrinsic(K1, D1);

  auto eigen_t = Eigen::Matrix<T,3,1>(-1.69648,  0.04953,  0.00468);
  eigen_t = 0.05 / eigen_t.norm() * eigen_t; // length, normalization.

  Eigen::Matrix<T,3,3> eigen_R;
  eigen_R << 0.9996627898663459, 0.0097117606966212, -0.02408294543459269,
      -0.008933540129790725, 0.9994410730091756, 0.03221387035140386,
      0.02438233822633555, -0.03198786154839366, 0.999190811755281;

  g_rl.setRotationMatrix(eigen_R);
  g_rl.translation() = eigen_t;

  boost::filesystem::directory_iterator it{im0_path}, end;

  feature_criteria = NULL;

  for(; it != end; it++)
  {
    std::string str = it->path().filename().stem().string();
    if(it->path().filename().extension() != ".png")
    {
      std::cout << it->path().filename() << std::endl;
      std::cout << it->path().filename().extension() << std::endl;
      std::cout << "not png" << std::endl;
      exit(1);
    }

    size_t i = std::stoi(str);

    im0_filenames[i] = it->path().string();
    im1_filenames[i] = im1_path+"/" + it->path().filename().string();

    if(!feature_criteria)
    {
      cv::Mat src = cv::imread(it->path().string());
      feature_criteria = new RisFeatureCriteria(src.cols, src.rows);
    }
  }
}
#endif
